NAME ?= cub3D
BONUS_NAME ?=

BUILD_DIR ?= ./objs
SRC_DIRS ?= ./srcs
INCL_DIR ?= ./include

LIB = libft-42
LIBMLX = MLX42
LIBS = $(addprefix -L ,$(LIB) $(LIBMLX)/build) -lglfw -lm
# added -lm (math lib), macos might need "-lmx"
# LIBS = $(addprefix -L ,$(LIB) $(LIBMLX)/build) -L /opt/homebrew/lib -lglfw -framework OpenGL

SRCS := $(filter-out %_bonus.c, $(shell find $(SRC_DIRS) -name *.c))
OBJS := $(subst $(SRC_DIRS), $(BUILD_DIR), $(SRCS:.c=.o))

BONUS_SRCS := $(shell find $(SRC_DIRS) -name *_bonus.c)
BONUS_OBJS := $(subst $(SRC_DIRS), $(BUILD_DIR), $(BONUS_SRCS:.c=.o))

INC_DIRS := $(shell find $(INCL_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC = cc
CFLAGS ?= $(INC_FLAGS) -Wall -Werror -Wextra -MMD -MP -g

LD = cc

all: init_submodules $(NAME)

# improve by making -lft -lmlx42 modular
$(NAME): $(OBJS)
	@make -C $(LIB)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@make libmlx
	@echo "\nLinking:"
	$(LD) $(LIBS) -o $@ $(OBJS) -lft -lmlx42
	@echo "..\n"

$(BUILD_DIR)/%.o: $(SRC_DIRS)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $< ..\n"

bonus: init_submodules $(BONUS_NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(BONUS_NAME): $(BONUS_OBJS)
	@make -C $(LIB)
	@echo "\nlinking bonus:"
	$(LD) $(LDFLAGS) -o $(BONUS_NAME) $(BONUS_OBJS) $(LINKS)
	@echo "..\n"

$(BUILD_DIR)/%_bonus.o: $(SRC_DIRS)/%_bonus.c
	$(HIDE) mkdir -p $(@D)
	$(HIDE) $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "Compiling $< ...\n"

clean:
	$(HIDE) $(RM) -r $(BUILD_DIR)
	$(MAKE) -C $(LIB) clean
	@rm -rf $(LIBMLX)/build
	@echo "removing obj/ ..\n"

fclean: clean
	@make fclean -C $(LIB)
	$(HIDE) $(RM) $(NAME)
	$(HIDE) $(RM) $(BONUS_NAME)
	$(MAKE) -C $(LIB) fclean
	@echo "removing $(NAME) ..\n"

re: fclean all

init_submodules:
	@git submodule update --init

commit: fclean
	git add .
	git commit -m "$(m)"
	git push origin main

# make maptest 2>&1 | grep --color=always -B 1 "Segmentation fault"
maptest: all
	-./$(NAME) maps/bad_file_path/map03.cub
	-./$(NAME) maps/bad_open/map00_left_top_space.cub
	-./$(NAME) maps/bad_open/map00_left_top_zero.cub
	-./$(NAME) maps/bad_open/map00_right_btm_0.cub
	-./$(NAME) maps/bad_open/map00_right_btm_eof.cub
	-./$(NAME) maps/bad_open/map00_right_btm_nl.cub
	-./$(NAME) maps/bad_open/map00_right_top_nl.cub
	-./$(NAME) maps/bad_open/map00_right_top_space.cub
	-./$(NAME) maps/bad_open/map00_right_top_zero.cub
	-./$(NAME) maps/bad_open/map01.cub
	-./$(NAME) maps/map_should_error/a.cub
	-./$(NAME) maps/map_should_error/asciiart_dot_eu2.cub
	-./$(NAME) maps/map_should_error/bad_color.cub
	-./$(NAME) maps/map_should_error/codepen_io_MittenedWatchmaker.cub
	-./$(NAME) maps/map_should_error/extension_missing
	-./$(NAME) maps/map_should_error/map04small_space_in_col.cub
	-./$(NAME) maps/map_should_error/map08missing_start.cub
	-./$(NAME) maps/map_should_error/map09.cub
	-./$(NAME) maps/map_should_error/map_missing_texture.cub
	-./$(NAME) maps/map_should_error/map_nl.cub
	-./$(NAME) maps/map_should_error/map_pdf_missing_wall.cub
	-./$(NAME) maps/map_should_error/map_wikipedia.cub
	-./$(NAME) maps/map_should_error/no_space_path.cub
	-./$(NAME) maps/map_should_error/open_two_n.cub
	-./$(NAME) maps/map_should_error/single_n.cub
	-./$(NAME) maps/map_should_error/small_open.cub
	-./$(NAME) maps/map_should_error/wall_hole.cubb
	-./$(NAME) maps/map_should_ok/asciiart_dot_eu.cub
	-./$(NAME) maps/map_should_ok/l.cub
	-./$(NAME) maps/map_should_ok/map02.cub
	-./$(NAME) maps/map_should_ok/map03.cub
	-./$(NAME) maps/map_should_ok/map04small2.cub
	-./$(NAME) maps/map_should_ok/map04small.cub
	-./$(NAME) maps/map_should_ok/map04small_space_in_path.cub
	-./$(NAME) maps/map_should_ok/map05medium.cub
	-./$(NAME) maps/map_should_ok/map06big.cub
	-./$(NAME) maps/map_should_ok/map07S.cub
	-./$(NAME) maps/map_should_ok/map09.cub
	-./$(NAME) maps/map_should_ok/map10stairs.cub
	-./$(NAME) maps/map_should_ok/map_pdf.cub
	-./$(NAME) maps/map_should_ok/n.cub
	-./$(NAME) maps/simple_fail/S.cub
	-./$(NAME) maps/simple_fail/nothing.cub
	-./$(NAME) maps/simple_fail/no_closing_right.cub
	-./$(NAME) maps/simple_fail/no_closing_bottom.cub
	-./$(NAME) maps/simple_fail/0.cub
	-./$(NAME) maps/simple_fail/no_closing_top.cub
	-./$(NAME) maps/simple_fail/no_closing_left.cub

.PHONY: clean fclean re all bonus init_submodules libmlx commit maptest