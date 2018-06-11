/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** main
*/

#include <malloc.h>
#include "communication.h"
#include "game.h"

t_opts *init_opts(void)
{
	t_opts *elem = malloc(sizeof(t_opts));

	if (!elem)
		return (NULL);
	elem->port = DEFAULT_VALUE;
	elem->x = DEFAULT_VALUE;
	elem->y = DEFAULT_VALUE;
	elem->teams = NULL;
	elem->max_clients = DEFAULT_VALUE;
	elem->freq = 100;
	return (elem);
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

void clear_server(t_server *server)
{
	free(server->opts);
	remove_all_clients(server->clients);
	remove_all_messages(server);
}

int main(int ac, char **av)
{
	t_server server;
	t_opts *opts = init_opts();

	server.opts = opts;
	server.clients = NULL;
	server.messages = NULL;
	manage_command(ac, av, server.opts);
	server.socket = create_socket(server.opts->port, INADDR_ANY, SERVER);
	game_loop(&server);
	clear_server(&server);
	return (SUCCESS);
}