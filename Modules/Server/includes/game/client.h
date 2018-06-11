/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client
*/

#pragma once

#include <stddef.h>

typedef struct s_client {
	int fd;
	size_t team_id;
	size_t player_id;
	struct s_client *next;
} t_client;