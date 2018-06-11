##
## EPITECH PROJECT, 2018
## server_zappy ()
## File description:
## Makefile
##

NAME		=	zappy_server

SERVER		=	Modules/Server

AI		=	Modules/AI

CC		=	gcc

all: 		server ai

server:
		make -sC $(SERVER)

ai:
		make -sC $(AI)

clean:
		make clean -sC $(AI)
		make clean -sC $(SERVER)

fclean: 	clean
		make fclean -sC $(AI)
		make fclean -sC $(SERVER)

re:		fclean all

.PHONY: 	all clean fclean re server ai
