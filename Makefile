##
## EPITECH PROJECT, 2018
## server_zappy ()
## File description:
## Makefile
##

NAME		=	zappy_server

SERVER		=	Modules/Server

AI		=	Modules/AI

GRAPHICAL	=	Modules/Graphical

all: 		graphical server ai

server:
		make -sC $(SERVER)

ai:
		make -sC $(AI)

graphical:
		make -sC $(GRAPHICAL)

clean:
		make clean -sC $(GRAPHICAL)
		make clean -sC $(AI)
		make clean -sC $(SERVER)

fclean: 	clean
		make fclean -sC $(GRAPHICAL)
		make fclean -sC $(AI)
		make fclean -sC $(SERVER)

re:		fclean all

.PHONY: 	all clean fclean re graphical server ai
