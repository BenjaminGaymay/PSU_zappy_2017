/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#pragma once

#include "arguments_ai.h"
#include "tools.h"

typedef enum {
	AI_LOOK,
	AI_EAT,
	AI_MOVE
} e_state;

typedef struct s_action {
	e_state state;
	char *action;
} t_action;

typedef struct s_ai {
	t_opts_ai *opts;
	int fd;
	e_state state;
} t_ai;

int run_ai(t_ai *);
int manage_sockets(t_ai *);
int look_for_ressources(t_ai *, const char *);
int try_incatation(t_ai *);
void receipt_welcome(t_ai *);
int receipt_infos(t_ai *ai);