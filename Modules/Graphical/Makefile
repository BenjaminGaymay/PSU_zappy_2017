##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME		= 	zappy_graphical

CC			= 	g++

SHARED		=	../Shared

GRAPHICAL	= 	Modules/GRAPHICAL

RM			= 	rm -f

SRCS		= 	srcs/main.cpp				\
	  			srcs/font.cpp				\
	  			srcs/mouse.cpp				\
	  			srcs/text.cpp				\
	  			srcs/textureAndSprite.cpp	\

OBJS		= 	$(SRCS:.cpp=.o)

CPPFLAGS = 	-I includes/				\
			-I $(SHARED)/includes

CPPFLAGS += 	-W -Wall -Wextra

LDFLAGS	= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

all: 		$(NAME)
		mv $(NAME) ../..

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

re: fclean all

.PHONY: all clean fclean re
