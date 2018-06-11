/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** arguments
*/

#pragma once

#include <stdbool.h>

typedef struct s_opts {
	int port;
	char *name;
	char *machine;
} t_opts;

typedef struct s_args {
	char *flag;
	int (*function)(char **, t_opts *);
} t_args;

int manage_commands(char **, t_opts *);

int help(char **, t_opts *);
int port(char **, t_opts *);
int name(char **, t_opts *);
int machine(char **, t_opts *);

bool check_commands(t_opts *);