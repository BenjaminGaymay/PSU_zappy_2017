##
## EPITECH PROJECT, 2018
## server_zappy ()
## File description:
## Makefile
##

NAME	=	zappy_server

CC	=	gcc

SHARED	=	../Shared

RM	= 	rm -f

SRCS	=	./srcs/main.c				\
		./srcs/arguments/args_fct.c		\
		./srcs/arguments/arguments.c		\
		./srcs/map/create_map.c			\
		./srcs/communication/socket_infos.c	\
		./srcs/communication/manage_messages.c	\
		./srcs/game/game_loop.c			\
		$(SHARED)/srcs/connection/sockets.c	\
		$(SHARED)/srcs/tools/array_tools.c	\
		$(SHARED)/srcs/tools/count_row.c	\
		$(SHARED)/srcs/tools/string_tools.c

OBJS	=	$(SRCS:.c=.o)


CFLAGS	=	-I./includes			\
		-I./includes/arguments		\
		-I./includes/map		\
		-I./includes/game		\
		-I./includes/communication	\
		-I$(SHARED)/includes

CFLAGS	+=	-W -Wall -Wextra -g3

LDFLAGS =

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 		$(NAME) $(NAME)
		cp $(NAME) ../..


$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'

clean:
		@$(RM) $(OBJS) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean: 	clean
		@$(RM) $(NAME) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
		$(RM) ../../$(NAME)

re:		fclean all

.PHONY: 	all clean fclean re
