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

t_map **create_map(int y, int x)
{
	srand(time(NULL));
	t_map **map;

	map = calloc(y + 1, sizeof(t_map *));
	for (int i = 0; i < y; ++i) {
		map[i] = calloc(x + 1, sizeof(t_map));
		for (int j = 0; j < x; ++j) {
			map[i][j].linemate = rand() % 2;
			map[i][j].sibur = rand() % 2;
		}
	}
	for (int i = 0; i < y; ++i) {
		printf("%d - ", i);
		for (int j = 0; j < x; ++j) {
			printf("%ld ", map[i][j].linemate);
		}
		printf("\n");
	}
	return (map);
}