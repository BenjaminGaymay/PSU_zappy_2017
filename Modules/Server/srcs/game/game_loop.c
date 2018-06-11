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
		manage_sockets(server);
	}
	return (1);
}