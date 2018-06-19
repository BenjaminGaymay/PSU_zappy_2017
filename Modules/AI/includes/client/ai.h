/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#pragma once

#include "arguments_ai.h"
#include "ai_list.h"
#include "tools.h"

/*
** Structures
*/

typedef struct s_action {
	char *str;
	e_element elem;
} t_action;

typedef struct s_ai {
	t_opts_ai *opts;
	int fd;
	size_t level;
	size_t inv[7];
	t_request *list;
} t_ai;

typedef struct s_response {
	char *msg;
	int (*fct)(t_ai *, char *);
} t_response;

/*
** Prototypes
*/

int run_ai(t_ai *);
int manage_sockets(t_ai *);
int look_for_ressources(t_ai *, const char *);
int try_incantation(t_ai *);
int receipt_welcome(t_ai *);
void send_command(t_ai *, const char *);
char *readline(const int);
bool compare_elevation(const size_t *, const size_t *);
int drop_needed_items(int, size_t *);
int wait_for_response(t_ai *);