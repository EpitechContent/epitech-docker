

NAME		=	libpreload.so
LIB		=	-L./../../ -llapin \
			-L/usr/lib64 \
			-lsfml-audio \
			-lsfml-graphics \
			-lsfml-window \
			-lsfml-system \
			-lstdc++ -ldl
FLAG		=	-W -Wall -ansi -pedantic -g -g3 -ggdb -lm
SRC		=	$(wildcard ./*.c)
OBJ		=	$(SRC:.c=.o)

all:		$(NAME)
$(NAME):	$(OBJ)
		gcc -shared $(OBJ) $(LIB) -o $(NAME)
clean:
		rm -f $(OBJ)
fclean:		clean
		rm -f $(NAME)
re:		fclean all
.c.o:
	gcc -fPIC -c $< -o $@ $(FLAG)

