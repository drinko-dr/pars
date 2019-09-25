$(SRCS) = *.c

$(OBJ) = *.o

$(NAME) = fillit

$(HEADER) = fillit.h

all: $(NAME)

$(NAME):
	gcc -c $(SRCS)
	gcc -o $(NAME) $(OBJ) -I$(HEADER)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	fclean all
