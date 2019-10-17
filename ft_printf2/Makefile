NAME = libftprintf.a

SRC = ft_printf.c

OBJ = ft_printf.o

HEADER = ft_printf.h

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o:%.c $(HEADER)
	@gcc -Wall -Wextra -Werror -I . -c $< -o $@
clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

all: $(NAME)

re: fclean all
