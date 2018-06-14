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

char *is_graphical(t_server *server, t_message *cmd)
{
	t_client *client = cmd->owner;
	t_graphical_client *g_client;

	cmd->finish_date = time_until_finish(0, server->opts->freq);
	g_client = client_to_graphical(server, cmd->owner);
	unlink_client_messages(server, cmd->owner);
	remove_client(server, client, false);
	dprintf(g_client->socket, "msz %d %d\n", server->opts->x, server->opts->y);
	return (NULL);
}