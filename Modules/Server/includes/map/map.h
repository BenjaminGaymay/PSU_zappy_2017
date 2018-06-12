/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** arguments
*/

#pragma once

#include <stdlib.h>
#include <string.h>

typedef struct s_map {
	size_t linemate;
	size_t deraumere;
	size_t sibur;
	size_t mendiane;
	size_t phiras;
	size_t thystame;
	size_t food;
} t_map;

typedef struct s_get_type {
	size_t x;
	const char *str;
} t_get_type;

typedef struct s_pos {
	int x;
	int y;
} t_pos;

t_map **create_map(int, int);