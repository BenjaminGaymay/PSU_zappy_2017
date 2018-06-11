/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** main
*/

#include "macro.h"
#include "server.h"
#include "arguments.h"

int main(int ac, char **av)
{
	t_opts opts;

	manage_command(ac, av, &opts);
	printf("port : %d\nwidth : %d\nheight : %d\nclients : %d\nfreq : %d\n", opts.port, opts.x, opts.y, opts.max_clients, opts.freq);
	return 0;
}