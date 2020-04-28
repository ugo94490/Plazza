##
## EPITECH PROJECT, 2020
## OOP_arcade_2019
## File description:
## Makefile
##

SRC	=	main.cpp

OBJ	=	$(SRC:.cpp=.o)

NAME	=	plazza

CPPFLAGS	=	-I./include

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
