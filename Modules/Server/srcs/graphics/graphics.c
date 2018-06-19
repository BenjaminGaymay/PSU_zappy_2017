/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** graphics
*/

#include "communication.h"
#include "manage_time.h"
#include "server.h"
#include "client.h"

static t_graphical_client *client_to_graphical(t_server *server, t_client *client)
{
	static size_t id = 0;
	t_graphical_client *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), NULL);
	printf("New graphical client - %ld\n", id);
	new->id = id++;
	new->socket = client->socket;
	new->next = server->graphical_client;
	server->graphical_client = new;
	return (new);
}

void is_graphical(t_server *server, t_client *client)
{
	t_graphical_client *g_client;
	t_inventory c;

	g_client = client_to_graphical(server, client);
	remove_client(server, client, false);
	dprintf(g_client->socket, "msz %d %d\n", server->opts->x, server->opts->y);
	for (size_t i = 0 ; server->opts->teams[i] ; i++)
		dprintf(g_client->socket, "tna %s\n", server->opts->teams[i]->name);
	for (int i = 0 ; i < server->opts->y ; i++) {
		for (int f = 0 ; f < server->opts->x  ; f++) {
			c = server->map[i][f];
			dprintf(g_client->socket,
				"bct %d %d %ld %ld %ld %ld %ld %ld %ld\n", f, i,
				c.food, c.linemate, c.deraumere, c.sibur,
				c.mendiane, c.phiras, c.thystame);
			usleep(200);
		}

	}
}