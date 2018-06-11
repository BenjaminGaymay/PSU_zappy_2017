/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** socket_infos
*/

#include "server.h"
#include "client.h"

static bool is_main_socket_written(int socket, fd_set *fd_read)
{
	struct timeval tv = {0, 50};

	FD_ZERO(fd_read);
	FD_SET(socket, fd_read);
	if (select(socket + 1, fd_read, NULL, NULL, &tv) == -1)
		FCT_FAILED("select");
	return FD_ISSET(socket, fd_read);
}

int add_client(t_server *server)
{
	static int id = 0;
	struct sockaddr_in client_sin;
	socklen_t client_sin_len;
	t_client *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	client_sin_len = sizeof(client_sin);
	new->player_id = id++;
	new->fd = accept(server->socket, (struct sockaddr *)&client_sin,
		&client_sin_len);
	new->next = server->clients;
	server->clients = new;
	printf("New client - %d\n", id);
	return (SUCCESS);
}

int manage_sockets(t_server *server)
{
	static fd_set fd_read;

	if (is_main_socket_written(server->socket, &fd_read) &&
			add_client(server) == ERROR)
		return (ERROR);
	return (SUCCESS);
}