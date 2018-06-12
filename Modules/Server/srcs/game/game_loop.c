/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game_loop
*/

#include "communication.h"
#include "manage_time.h"
#include "client.h"
#include "game.h"

int game_loop(t_server *server)
{
	while (1) {
		if (manage_sockets(server) == ERROR)
			return (ERROR);
		read_all_messages(server->messages);
		send_responses(server->messages);
		remove_all_messages(server);
	}
	return (SUCCESS);
}