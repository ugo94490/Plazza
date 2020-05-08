##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	main.cpp		\
		src/Americana.cpp	\
		src/APizza.cpp		\
		src/Fantasia.cpp	\
		src/Regina.cpp		\
		src/Margarita.cpp	\
		src/Kitchen.cpp		\
		src/Cook.cpp		\

OBJ	=	$(SRC:.cpp=.o)

NAME	=	plazza

CPPFLAGS	=	-I./include -g3

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS) -Wall -Wextra -pthread -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
