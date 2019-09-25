$(NAME) = fillit

$(SRCS) = *.c

$(OBJ) = *.o

all: $(NAME)

$(NAME):
	gcc -c $(SRCS)
	gcc -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	fclean all