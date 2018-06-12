##
## EPITECH PROJECT, 2018
## server_zappy ()
## File description:
## Makefile
##

NAME		=	zappy_server

SERVER		=	Modules/Server

AI		=	Modules/AI

GRAPHICAL	= Modules/Graphical

CC		=	gcc

all: 		server ai graphical

server:
		make -sC $(SERVER)

ai:
		make -sC $(AI)

graphical:
		make -sC $(GRAPHICAL)

clean:
		make clean -sC $(AI)
		make clean -sC $(SERVER)
		make clean -sC $(GRAPHICAL)

fclean: 	clean
		make fclean -sC $(AI)
		make fclean -sC $(SERVER)
		make fclean -sC $(GRAPHICAL)

re:		fclean all

.PHONY: 	all clean fclean re server ai
