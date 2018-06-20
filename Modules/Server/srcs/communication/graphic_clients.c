/*
** EPITECH PROJECT, 2018
** student
** File description:
** 20/06/18
*/

#include "server.h"

void send_to_graphics(t_server *server, char *msg)
{
	t_graphical_client *tmp = server->graphical_client;

	while (tmp) {
		dprintf(server->graphical_client->socket, "%s\n", msg);
		tmp = tmp->next;
	}
}