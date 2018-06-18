/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation
*/

#include <unistd.h>
#include "ai.h"
#include "macro.h"
#include "tools.h"
#include "commands.h"

void parse_inventory(char *buf, t_elevation *current)
{
	char **tab = str_to_tab(buf, ",");
	(void)current;
	for (int i = 0; tab[i]; i++) {
		printf("INV : %s\n", tab[i]);
	}
}

int try_incantation(t_ai *ai)
{
	t_elevation current;
	char buf[4096];

	dprintf(ai->fd, INVENTORY);
	int size = read(ai->fd, buf, 4096);
	if (size > 0) {
		buf[size] = '\0';
		parse_inventory(buf, &current);
		// printf("INVENTORY %s\n", buf);
		return (SUCCESS);
	}
	return (ERROR);
}