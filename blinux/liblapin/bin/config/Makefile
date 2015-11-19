

NAME		=	config
LIB		=	-L./../../ -llapin \
			-L/usr/local/lib/ \
			-lsfml-audio \
			-lsfml-graphics \
			-lsfml-window \
			-lsfml-system \
			-lstdc++
FLAG		=	-W -Wall -Werror -g -g3 -ggdb -lm
SRC		=	$(wildcard ./*.c)
OBJ		=	$(SRC:.c=.o)


all:		$(NAME)
$(NAME):	$(OBJ)
		gcc $(OBJ) $(LIB) -o $(NAME)
clean:
		rm -f $(OBJ)
fclean:		clean
		rm -f $(NAME)
re:		fclean all
.c.o:
	gcc -c $< -o $@ $(FLAG)

