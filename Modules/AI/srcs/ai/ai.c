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

char **get_data_from_look(const char *str)
{
	char **tab = NULL;
	char *tmp = NULL;

	if (!str)
		return (NULL);
	tmp = strdup(str);
	if (!tmp)
		return (NULL);
	replace_str((char *)tmp, ",,", " ");
	tab = str_to_tab((char *)tmp, ",");
	for (int i = 0; tab[i]; i++) {
		tab[i] = lstrip_m(tab[i], "[ ");
		tab[i] = rstrip_m(tab[i], "] ");
	}
	free(tmp);
	return (tab);
}

// static void find_forward(t_ai *ai)
// {
// 	char **tab = get_data_from_look(ai->look);
// 	// size_t i = 0;
// 	// size_t j = 2;

// 	if (!tab)
// 		return;
// 	if (strlen(tab[0]) > 0)
// 		send_command(ai, FORWARD);
// 	free_tab(tab);
// 	return;
// 	// while (i < tablen((char **)tab)) {
// 	// 	if (strcmp(tab[i], "") != 0) {
// 	// 		send_command(ai, FORWARD);
// 	// 		break;
// 	// 	}
// 	// 	i += j;
// 	// 	j += 2;
// 	// }
// 	// free_tab(tab);
// }

static int take_object(char **cmd, t_ai *ai)
{
	static const char *objects[] = {"linemate", "deraumere", "sibur",
		"mendiane", "phiras", "thystame", "food", NULL};
	char **tab = str_to_tab(cmd[0], " ");
	char msg[100];
	char *t;

	for (int i = 0; tab[i]; i++) {
		for (int j = 0; objects[j]; j++) {
			if (strcmp(tab[i], objects[j]) == 0) {
				sprintf(msg, "Take %s", tab[i]);
				send_command(ai, msg);
				t = readline(ai->fd);
				printf("%s\n", t);
				return (SUCCESS);
			}
		}
	}
	return (SUCCESS);
}

int look_for_ressources(t_ai *ai, const char *tmp)
{
	char **tab = get_data_from_look(tmp);
	bool no_res = true;
	int random_dir = rand() % 2;
	char t[4096];

	if (strcmp(tab[0], "") != 0)
		return (take_object(tab, ai));
	// find_forward((const char **)tab, ai, &no_res);
	if (no_res == false) {
		send_command(ai, random_dir == 0 ? TURN_LEFT : TURN_RIGHT);
		read(ai->fd, t, 4096);
	}
	return (SUCCESS);
}

int run_ai(t_ai *ai)
{
	t_associate_state arr[] = {
		{AI_LOOK, look_cmd},
		{AI_TAKE, take_cmd},
		{AI_MOVE, move_cmd},
		{AI_INCANT, incant_cmd},
		{AI_TURN, turn_cmd}
	};

	ai->state = AI_LOOK;
	if (receipt_welcome(ai))
		return (ERROR);
	while (ai->run) {
		if (listlen(ai->list) < 10)
			for (int i = 0; i < 4; i++)
				if (ai->state == arr[i].state)
					arr[i].fct(ai);
		wait_for_response(ai);
	}
	return (SUCCESS);
}
