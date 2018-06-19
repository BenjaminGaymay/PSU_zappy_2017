/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** socket_infos
*/

#include "communication.h"
#include "client.h"

static int get_max_fd(t_server *server)
{
	int max = server->socket;
	t_client *tmp = server->clients;

	while (tmp) {
		max = (tmp->socket > max ? tmp->socket : max);
		tmp = tmp->next;
	}
	return (max);
}

static void reset_all_sockets(t_server *server, fd_set *fd_read)
{
	t_client *tmp = server->clients;

	FD_ZERO(fd_read);
	FD_SET(server->socket, fd_read);
	while (tmp) {
		FD_SET(tmp->socket, fd_read);
		tmp = tmp->next;
	}
}

static int read_on_client(t_server *server, t_client *client)
{
	static char buffer[4096];
	int size;
	char *tmp = NULL;

	size = read(client->socket, buffer, 4096);
	if (size > 0) {
		buffer[size] = '\0';
		tmp = strtok(buffer, "\n");
		while (tmp && client->request_number < 10) {
			if (!client->team)
				find_team(server, client, tmp);
			else if (add_message_in_list(server, client, tmp) == ERROR)
				return (ERROR);
			else
				client->request_number += 1;
			tmp = strtok(NULL, "\n");
		}
	}
	else
		return (remove_client(server, client, true), ERROR);
	return (SUCCESS);
}

static int are_clients_written(t_server *server, fd_set *fd_read)
{
	t_client *tmp = server->clients;

	while (tmp) {
		if (FD_ISSET(tmp->socket, fd_read))
			tmp = (read_on_client(server, tmp) == ERROR ? server->clients : tmp->next);
		else
			tmp = tmp->next;
	}
	return (SUCCESS);
}

int manage_sockets(t_server *server)
{
	static fd_set fd_read;
	struct timeval tv = {0, 50};

	reset_all_sockets(server, &fd_read);
	if (select(get_max_fd(server) + 1, &fd_read, NULL, NULL, &tv) == -1)
		return (FCT_FAILED("select"), ERROR);
	if (FD_ISSET(server->socket, &fd_read) && add_client(server) == ERROR)
		return (ERROR);
	return (are_clients_written(server, &fd_read));
}