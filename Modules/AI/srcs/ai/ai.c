/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "ai.h"
#include "macro.h"
#include "commands.h"

static void find_ressources(t_ai *ai, t_action *action)
{
	for (int i = 0; i < 3; i++)
		if (ai->state == action[i].state)
			dprintf(ai->fd, action[i].action);
}

int run_ai(t_ai *ai)
{
	t_action action[] = {
		{AI_LOOK, LOOK},
		{AI_EAT, TURN_LEFT},
		{AI_MOVE, FORWARD}
	};
	int a = 0;

	srand(time(NULL));
	while (true) {
		a = rand() % 2;
		ai->state = a;
		find_ressources(ai, action);
		dprintf(ai->fd, FORWARD);
		manage_sockets(ai);
	}
	return (SUCCESS);
}