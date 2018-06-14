/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#pragma once

#include "arguments_ai.h"

typedef struct s_ai {
	t_opts_ai *opts;
	int fd;
} t_ai;

int run_ai(t_ai *);
int manage_sockets(t_ai *ai);