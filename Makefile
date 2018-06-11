NAME		=	zappy_server

RS		=	Modules/Server

AI		=	Modules/AI

CC		=	gcc

SRCS_SERVER	=	$(RS)/srcs/main.c			\
			$(RS)/srcs/arguments/args_fct.c		\
			$(RS)/srcs/arguments/arguments.c	\
			$(RS)/srcs/tools/array_tools.c		\
			$(RS)/srcs/tools/string_tools.c		\
			$(RS)/srcs/tools/count_row.c		\
			$(RS)/srcs/team.c 			\
			$(RS)/srcs/map/create_map.c		\
			$(RS)/srcs/connection/sockets.c		\
			$(RS)/srcs/connection/socket_infos.c	\
			$(RS)/srcs/game/game_loop.c



SRCS_AI		=	$(AI)/srcs/main.c

OBJS		=	$(SRCS_SERVER:.c=.o)

CFLAGS	=	-I $(RS)/includes		\
		-I $(RS)/includes/arguments	\
		-I $(RS)/includes/tools		\
		-I $(RS)/includes/map		\
		-I $(RS)/includes/connection	\
		-I $(RS)/includes/game

CFLAGS		+=	-W -Wall -Wextra -g3

LDFLAGS =

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 		$(NAME)

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
