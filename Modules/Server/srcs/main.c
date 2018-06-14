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
	remove_all_clients(server->clients);
	remove_all_messages(server);
	remove_map(server->map, server->opts->y);
	// Free clients graphiques
	free(server->opts);
	close(server->socket);
}

static bool check_valid_options(t_opts *opt)
{
	return (!(opt->port <= 0 ||
		opt->x == DEFAULT_VALUE ||
		opt->y == DEFAULT_VALUE ||
		opt->teams == NULL ||
		opt->max_clients == DEFAULT_VALUE));
}

int main(int ac, char **av)
{
	t_opts *opts = init_opts();
	t_server server = {opts, NULL, NULL, NULL, NULL, DEFAULT_VALUE};

	if (manage_command(ac, av, server.opts) == ERROR ||
		!check_valid_options(server.opts))
		return (free(opts), fprintf(stderr, "Bad arguments.\n"),  ERROR);
	server.socket = create_socket(server.opts->port, INADDR_ANY, SERVER);
	server.map = create_map(server.opts->y, server.opts->x);
	game_loop(&server);
	clear_server(&server);
	return (SUCCESS);
}