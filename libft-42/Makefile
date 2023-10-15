CC = cc
CFLAGS = -Wall -Werror -Wextra -g
RM = rm -f
NAME = libft.a

SRCS = $(wildcard *.c)
OBJDIR = obj
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

bonus: $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)

clean:
	-${RM} ${OBJECTS} ${SRCS:.c=.d} a.out
	-${RM} -r ${OBJDIR}
	-${RM} ${SRCS:.c=.d}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re bonus
