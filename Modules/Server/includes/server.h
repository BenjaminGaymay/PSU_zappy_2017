/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** server
*/

#pragma once

#include <stdbool.h>
#include "macro.h"
#include "arguments_server.h"
#include "sockets.h"
#include "map.h"

typedef struct s_client {
	int socket;
	size_t team_id;
	size_t player_id;
	struct s_client *next;
} t_client;

typedef struct s_message {
	t_client *owner;
	char *request;
	char *response;
	struct s_message *next;
} t_message;

typedef struct s_server {
	t_opts *opts;
	t_client *clients;
	t_message *messages;
	int socket;
} t_server;

size_t count_row(char **);