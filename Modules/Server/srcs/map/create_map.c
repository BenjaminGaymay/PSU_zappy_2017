/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include "map.h"
#include "macro.h"
#include "arguments.h"

int **create_map(size_t y, size_t x)
{
	int **av;

	av = calloc(y + 1, sizeof(int *));
	for (size_t i = 0; i < y; ++i) {
		av[i] = calloc(x + 1, sizeof(int));
	}

	for (size_t i = 0; i < y; ++i) {
		printf("%ld - ", i);
		for (size_t j = 0; j < x; ++j) {
			printf("%d", av[i][j]);
		}
		printf("\n");
	}
	return (av);
}