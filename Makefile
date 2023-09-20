NAME ?= cub3d
BONUS_NAME ?=

BUILD_DIR ?= ./objs
SRC_DIRS ?= ./srcs
INCL_DIR ?= ./include

LIB = libft-42
LIBMLX = MLX42
LIBS = $(addprefix -L ,$(LIB) $(LIBMLX)/build)

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
	chmod -r maps/norights.cub

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

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

commit: fclean
	chmod +r maps/norights.cub
	git add .
	git commit -m "$(m)"
	git push origin main

.PHONY: clean fclean re all bonus init_submodules valgrind libmlx commit