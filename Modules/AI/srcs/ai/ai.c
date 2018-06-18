/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#include <stdlib.h>
#include <unistd.h>
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

static int take_object(char **cmd, t_ai *ai)
{
	char **tab = str_to_tab(cmd[0], " ");
	char msg[100];

	if (strcmp(tab[0], "ko") == 0 ||
		strcmp(tab[0], "dead") == 0)
		return (ERROR);
	sprintf(msg, "Take %s\n", tab[0]);
	printf(msg);
	dprintf(ai->fd, msg);
	return (SUCCESS);
}

int look_for_ressources(t_ai *ai, const char *tmp)
{
	char **tab = get_data_from_look(tmp);
	bool no_res = true;
	int random_dir = rand() % 2;

	if (strcmp(tab[0], "") != 0)
		return take_object(tab, ai);
	find_forward((const char **)tab, ai, &no_res);
	if (no_res == false)
		dprintf(ai->fd, random_dir == 0 ? TURN_LEFT : TURN_RIGHT);
	return (SUCCESS);
}

int run_ai(t_ai *ai)
{
	dprintf(ai->fd, "%s\n", ai->opts->name);
	while (true) {
		if (ai->state == AI_LOOK)
			dprintf(ai->fd, LOOK);
		manage_sockets(ai);
	}
	return (SUCCESS);
}