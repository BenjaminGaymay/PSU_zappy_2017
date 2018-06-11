##
## EPITECH PROJECT, 2018
## PSU_zappy_2017
## File description:
## Makefile
##

NAME	= zappy_ai

CC	= gcc

AI	= Modules/AI

RM	= rm -f

SRCS	= ./srcs/main.c			\
	  ./srcs/arguments/arguments.c	\
	  ./srcs/arguments/args_fct.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I./includes/			\
	 -I./includes/arguments/
CFLAGS += -W -Wall -Wextra

all: $(NAME)
	cp $(NAME) ../..
$(NAME): $(OBJS)
	 $(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ../../$(NAME)

re: fclean all

.PHONY: all clean fclean re
