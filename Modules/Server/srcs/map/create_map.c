/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include <time.h>
#include "map.h"
#include "macro.h"
#include "arguments_server.h"

t_inventory **create_map(int y, int x)
{
	srand(time(NULL));
	t_inventory **map;

	map = calloc(y + 1, sizeof(t_inventory *));
	for (int i = 0; i < y; ++i) {
		map[i] = calloc(x + 1, sizeof(t_inventory));
		for (int j = 0; j < x; ++j) {
			map[i][j].linemate = rand() % 2;
			map[i][j].sibur = rand() % 2;
		}
	}
	for (int i = 0; i < y; ++i) {
		for (int j = 0; j < x; ++j) {
			printf("%ld ", map[i][j].linemate);
		}
	}
	return (map);
}

void remove_map(t_inventory **map, int y)
{
	for (int i = 0; i < y; ++i)
		free(map[i]);
	free(map);
}