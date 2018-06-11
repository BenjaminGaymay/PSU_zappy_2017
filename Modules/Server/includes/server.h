/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include "macro.h"
#include "arguments.h"
#include "sockets.h"
#include "client.h"
#include "map.h"

typedef struct s_server {
	t_opts *opts;
	t_client *clients;
	int *team;
	int socket;
} t_server;

size_t count_row(char **array);
bool add_team_member(t_server *server, char *team_name);
bool remove_team_member(t_server *server, char *team_name);
bool init_team(t_server *server);