

NAME		=	music
LIB		=	-L./../../ -llapin \
			-L/usr/lib64 \
			-lsfml-audio \
			-lsfml-graphics \
			-lsfml-window \
			-lsfml-system \
			-lstdc++
FLAG		=	-W -Wall -Werror -ansi -pedantic -g -g3 -ggdb -lm
SRC		=	$(wildcard ./*.c)
OBJ		=	$(SRC:.c=.o)


all:		$(NAME)
$(NAME):	$(OBJ)
		gcc $(OBJ) $(LIB) -o music
clean:
		rm -f $(OBJ)
fclean:		clean
		rm -f $(NAME)
re:		fclean all
.c.o:
	gcc -c $< -o $@ $(FLAG)

