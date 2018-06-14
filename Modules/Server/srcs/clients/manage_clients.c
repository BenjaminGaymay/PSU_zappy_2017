/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_clients
*/

#include "client.h"
#include "manage_time.h"
#include "communication.h"

int add_client(t_server *server)
{
	static size_t id = 0;
	struct sockaddr_in client_sin;
	socklen_t client_sin_len;
	t_client *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	client_sin_len = sizeof(client_sin);
	new->request_number = 0;
	new->player_id = id++;
	new->socket = accept(server->socket, (struct sockaddr *)&client_sin,
		&client_sin_len);
	new->occupied = false;
	new->lives = 10;
	new->last_eat = time_until_finish(LIFE_TIME, server->opts->freq);
	new->inventory = (t_inventory){0, 0, 0, 0, 0, 0, 0};
	new->level = 1;
	new->pos = (t_pos){0, 0};
	new->look = 0;
	new->next = server->clients;
	server->clients = new;
	return (SUCCESS);
}

void unlink_client_messages(t_server *server, t_client *client)
{
	t_message *tmp = server->messages;

	while (tmp) {
		if (tmp->owner->player_id == client->player_id)
			tmp->owner = NULL;
		tmp = tmp->next;
	}
}

void remove_client(t_server *server, t_client *client, bool close_fd)
{
	t_client *tmp = server->clients;

	if (client->player_id == tmp->player_id)
		server->clients = client->next;
	else {
		while (tmp->next && tmp->next->player_id != client->player_id)
			tmp = tmp->next;
		tmp->next = client->next;
	}
	if (close_fd && is_fd_open(client->socket)) {
		dprintf(client->socket, "dead\n");
		close(client->socket);
	}
	free(client);
}

void remove_all_clients(t_client *clients)
{
	t_client *client = clients;

	while (clients) {
		client = clients->next;
		free(clients);
		clients = client;
	}
}

size_t get_clients_number(t_client *clients)
{
	t_client *client = clients;
	size_t i = 0;


	while (client) {
		i += 1;
		client = clients->next;
	}
	return (i);
}