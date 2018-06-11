##
## EPITECH PROJECT, 2018
## server_zappy (Espace de travail)
## File description:
## Makefile
##

NAME		=	zappy_server

CC		=	gcc

SRCS		=	./srcs/main.c			\
			./srcs/arguments/args_fct.c		\
			./srcs/arguments/arguments.c	\
			./srcs/tools/array_tools.c		\
			./srcs/tools/string_tools.c		\
			./srcs/tools/count_row.c		\
			./srcs/team.c 			\
			./srcs/map/create_map.c


OBJS		=	$(SRCS:.c=.o)


CFLAGS		=	-I ./includes		\
			-I ./includes/arguments	\
			-I ./includes/tools		\
			-I ./includes/map

CFLAGS		+=	-W -Wall -Wextra -g3

LDFLAGS =

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 		$(NAME) $(NAME)


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
re:		fclean all

.PHONY: 	all clean fclean re
