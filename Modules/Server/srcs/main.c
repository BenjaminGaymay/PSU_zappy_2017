/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** main
*/

#include <malloc.h>
#include "communication.h"
#include "game.h"
#include "client.h"

static t_opts *init_opts(void)
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

static void clear_server(t_server *server)
{
	free(server->opts);
	remove_all_clients(server->clients);
	remove_all_messages(server);
	close(server->socket);
}

int main(int ac, char **av)
{
	t_opts *opts = init_opts();
	t_server server = {opts, NULL, NULL, -1, 0.0f};

	manage_command(ac, av, server.opts);
	server.socket = create_socket(server.opts->port, INADDR_ANY, SERVER);
	game_loop(&server);
	clear_server(&server);
	return (SUCCESS);
}