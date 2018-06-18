/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#pragma once

#include "arguments_ai.h"

typedef enum {
	AI_LOOK,
	AI_EAT,
	AI_MOVE
} e_state;

typedef struct s_vec2d {
	int x;
	int y;
} t_vec2d;

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
int manage_sockets(t_ai *ai);
int look_for_ressources(t_ai *, const char *);