NAME		=	zappy_server

AI_NAME		=	zappy_ai

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
			$(RS)/srcs/map/create_map.c



SRCS_AI		=	$(AI)/srcs/main.c

OBJS		=	$(SRCS_SERVER:.c=.o)

OBJS_AI		=	$(SRCS_AI:.c=.o)

CFLAGS_AI	=	-I $(AI)/includes

CFLAGS_AI	+=	-W -Wall -Wextra

CFLAGS	=	-I $(RS)/includes		\
		-I $(RS)/includes/arguments	\
		-I $(RS)/includes/tools		\
		-I $(RS)/includes/map

CFLAGS		+=	-W -Wall -Wextra -g3

LDFLAGS =

.c.o:
		@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ && \
		printf "[\033[1;32mcompiled\033[0m] % 29s\n" $< | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $< | tr ' ' '.'

all: 		$(NAME) $(AI_NAME)

$(NAME):	$(OBJS)
		@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(NAME) | tr ' ' '.'

$(AI_NAME):	$(OBJS_AI)
		@$(CC) $(OBJS_AI) -o $(AI_NAME) $(LDFLAGS) && \
		printf "[\033[1;36mbuilt\033[0m] % 32s\n" $(AI_NAME) | tr ' ' '.' || \
		printf "[\033[1;31mfailed\033[0m] % 31s\n" $(AI_NAME) | tr ' ' '.'

clean:
		@$(RM) $(OBJS) @$(RM) $(OBJS_AI) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(OBJS) | tr ' ' '.'

fclean: 	clean
		@$(RM) $(NAME)  @$(RM) $(AI_NAME) && \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.' || \
		printf "[\033[1;31mdeleted\033[0m] % 30s\n" $(NAME) | tr ' ' '.'
re:		fclean all

.PHONY: 	all clean fclean re
