/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tools
*/

#pragma once

#include <stdbool.h>
#include <stddef.h>

bool arr_contains(const char **, const char *);
int index_in_arr(const char **, const char *);
void free_tab(void **);
char **str_to_tab(char *, char *);
void show_tab(char **);

char *lstrip(char *, char *);
char *rstrip(char *, char *);
char char_to_upper(char);
void str_to_upper(char *);
int count_words(char *, char *);
bool is_number(char *);

typedef struct s_elevation {
	size_t player;
	size_t linemate;
	size_t deraumere;
	size_t sibur;
	size_t mendiane;
	size_t phiras;
	size_t thystame;
} t_elevation;

static const t_elevation g_elevation[] = {
	{1, 1, 0, 0, 0, 0, 0},
	{2, 1, 1, 1, 0, 0, 0},
	{2, 2, 0, 1, 0, 2, 0},
	{4, 1, 1, 2, 0, 1, 0},
	{4, 1, 2, 1, 3, 0, 0},
	{6, 1, 2, 3, 0, 1, 0},
	{6, 2, 2, 2, 2, 2, 1}
};