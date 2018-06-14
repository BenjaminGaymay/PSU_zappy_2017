/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** ai
*/

#include "ai.h"
#include "macro.h"
#include "commands.h"

int run_ai(t_ai *ai)
{
	while (true) {
		dprintf(ai->fd, LOOK);
		manage_sockets(ai);

	}
	return (SUCCESS);
}