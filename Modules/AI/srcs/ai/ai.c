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
			read(ai->fd, NULL, 4096);
			*no_res = false;
			break;
		}
		i += j;
		j += 2;
	}
}

static int take_object(char **cmd, t_ai *ai)
{
	static const char *objects[] = {"linemate", "deraumere", "sibur",
		"mendiane", "phiras", "thystame", "food", NULL};
	char **tab = str_to_tab(cmd[0], " ");
	char msg[100];

	for (int i = 0; tab[i]; i++) {
		for (int j = 0; objects[j]; j++) {
			if (strcmp(tab[i], objects[j]) == 0) {
				sprintf(msg, "Take %s\n", tab[i]);
				printf(msg);
				dprintf(ai->fd, msg);
				read(ai->fd, NULL, 4096);
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS);
}

int look_for_ressources(t_ai *ai, const char *tmp)
{
	static int first = 0;
	char **tab = get_data_from_look(tmp);
	bool no_res = true;
	int random_dir = rand() % 2;

	if (first <= 1)
		return (first++, SUCCESS);
	if (strcmp(tab[0], "") != 0)
		return take_object(tab, ai);
	find_forward((const char **)tab, ai, &no_res);
	if (no_res == false) {
		dprintf(ai->fd, random_dir == 0 ? TURN_LEFT : TURN_RIGHT);
		read(ai->fd, NULL, 4096);
	}
	return (SUCCESS);
}

int run_ai(t_ai *ai)
{
	receipt_welcome(ai);
	dprintf(ai->fd, "%s\n", ai->opts->name);
	receipt_infos(ai);
	while (true) {
		try_incatation(ai);
		dprintf(ai->fd, LOOK);
		manage_sockets(ai);
	}
	return (SUCCESS);
}