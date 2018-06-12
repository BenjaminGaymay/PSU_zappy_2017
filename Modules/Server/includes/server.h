/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include "arguments.h"
#include "map.h"

typedef struct s_server {
	t_opts *opts;
	int *team;
	t_map **map;
} t_server;

size_t count_row(char **array);
bool add_team_member(t_server *server, char *team_name);
bool remove_team_member(t_server *server, char *team_name);
bool init_team(t_server *server);

char *look_top(t_server, char *, t_pos);
char *look_right(t_server, char *, t_pos);
char *look_bot(t_server, char *, t_pos);
char *look_left(t_server, char *, t_pos);
char *look(t_server);
char *get_map_objects_top_bot(t_server, char *, t_pos);
char *get_map_objects_left_right(t_server, char *, t_pos);
