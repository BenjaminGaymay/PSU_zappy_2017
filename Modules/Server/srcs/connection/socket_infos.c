/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** socket_infos
*/

#include "server.h"
#include "client.h"

static int add_client(t_server *server)
{
	static size_t id = 0;
	struct sockaddr_in client_sin;
	socklen_t client_sin_len;
	t_client *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	client_sin_len = sizeof(client_sin);
	new->player_id = id++;
	new->socket = accept(server->socket, (struct sockaddr *)&client_sin,
		&client_sin_len);
	printf("New client - %ld\n", id - 1);
	new->next = server->clients;
	server->clients = new;
	return (SUCCESS);
}

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

static void remove_client(t_server *server, t_client *client)
{
	t_client *tmp = server->clients;

	if (client->player_id == tmp->player_id)
		server->clients = client->next;
	else {
		while (tmp->next && tmp->next->player_id != client->player_id)
			tmp = tmp->next;
		tmp->next = client->next;
	}
	printf("Client '%ld' out\n", client->player_id);
	free(client);
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
		while (tmp) {
			printf("MESSAGE - '%s'\n", tmp);
			tmp = strtok(NULL, "\n");
		}
	}
	else
		return (remove_client(server, client), ERROR);
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
	struct timeval tv = {1, 0};

	reset_all_sockets(server, &fd_read);
	if (select(get_max_fd(server) + 1, &fd_read, NULL, NULL, &tv) == -1)
		return (FCT_FAILED("select"), ERROR);
	if (FD_ISSET(server->socket, &fd_read) && add_client(server) == ERROR)
		return (ERROR);
	return (are_clients_written(server, &fd_read));
}