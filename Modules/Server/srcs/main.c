/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** main
*/

#include <malloc.h>
#include "server.h"
#include "game.h"

t_opts *init_opts()
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

int main(int ac, char **av)
{
	t_server server;
	t_opts *opts = init_opts();

	server.team = NULL;
	server.opts = opts;
	manage_command(ac, av, server.opts);
	printf("port : %d\nwidth : %d\nheight : %d\nclients : %d\nfreq : %d\n", server.opts->port, server.opts->x, server.opts->y, server.opts->max_clients, server.opts->freq);
	init_team(&server);
	create_map(10, 10);
	server.socket = create_socket(server.opts->port, INADDR_ANY, SERVER);
	game_loop(&server);
	free(opts);
	return 0;
}