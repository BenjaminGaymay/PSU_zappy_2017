/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "ai.h"
#include "macro.h"
#include "commands.h"
#include "tools.h"

static char **get_data_from_look(const char *tmp)
{
	char **tab;

	tmp = lstrip(rstrip((char *)tmp, "]"), "[");
	replace_str((char *)tmp, ",,", " ");
	tab = str_to_tab((char *)tmp, ",");
	for (int i = 0; tab[i]; i++)
		tab[i] = lstrip(tab[i], " ");
	return (tab);
}

static void find_forward(const char **tab, const t_ai *ai, bool *no_res)
{
	size_t i = 0;
	size_t j = 2;

	while (i < tablen((char **)tab)) {
		if (strcmp(tab[i], "") != 0) {
			dprintf(ai->fd, FORWARD);
			*no_res = false;
			break;
		}
		i += j;
		j += 2;
	}
}

int look_for_ressources(t_ai *ai, const char *tmp)
{
	char **tab = get_data_from_look(tmp);
	bool no_res = true;
	int random_dir = rand() % 2;

	if (strcmp(tab[0], "") != 0)
		return (dprintf(ai->fd, "Take linemate\n"), SUCCESS);
	find_forward((const char**)tab, ai, &no_res);
	if (no_res == false)
		dprintf(ai->fd, random_dir == 0 ? TURN_LEFT : TURN_RIGHT);
	return (SUCCESS);
}

int run_ai(t_ai *ai)
{
	srand(time(NULL));
	// t_action action[] = {
	// 	{AI_LOOK, LOOK},
	// 	{AI_EAT, TURN_LEFT},
	// 	{AI_MOVE, FORWARD}
	// };
	dprintf(ai->fd, LOOK);

	while (true) {
		if (ai->state == AI_LOOK)
			dprintf(ai->fd, LOOK);
		manage_sockets(ai);
	}
	// while (true) {
	// 	// a = rand() % 2;
	// 	// ai->state = a;
	// 	find_ressources(ai, action);
	// 	dprintf(ai->fd, FORWARD);
	// 	manage_sockets(ai);
	// }
	return (SUCCESS);
}