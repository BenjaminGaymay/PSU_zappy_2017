/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game_loop
*/

#include "server.h"
#include "game.h"

int game_loop(t_server *server)
{
	while (1) {
		if (manage_sockets(server) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}