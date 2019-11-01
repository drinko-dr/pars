NAME = libftprintf.a

SRC = ft_printf.c checker.c flags.c oxx_flags.c diu_flags.c display.c utils2.c align.c utils.c print_digit.c kludge.c just_unsig.c print_unsig.c flag_f.c utils_f.c

OBJ = ft_printf.o checker.o flags.o oxx_flags.o diu_flags.o display.o utils2.o align.o utils.o print_digit.o kludge.o just_unsig.o print_unsig.o flag_f.o utils_f.o

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
