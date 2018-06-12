/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_clients
*/

#include "client.h"

int add_client(t_server *server)
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
	new->inventory = (t_inventory){0, 0, 0, 0, 0, 0, 0};
	new->level = 1;
	new->pos = (t_pos){0, 0};
	new->look = 0;
	printf("New client - %ld\n", id - 1);
	new->next = server->clients;
	server->clients = new;
	get_client_inventory(server->clients);
	return (SUCCESS);
}

void remove_client(t_server *server, t_client *client)
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

void remove_all_clients(t_client *clients)
{
	t_client *client = clients;

	while (clients) {
		client = clients->next;
		free(clients);
		clients = client;
	}
}