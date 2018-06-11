/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "arguments.h"

int port(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->port = atoi(av[0]);
	if (opt->port <= 0)
		return (fprintf(stderr, "Error: port must be positif.\n"), ERROR);
	return (SUCCESS);
}

int width(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->x = atoi(av[0]);
	return (SUCCESS);
}

int height(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->y = atoi(av[0]);
	return (SUCCESS);
}

int name(char **av, t_opts *opt)
{
	int h = 0;
	size_t len = 0;

	if (!av[0])
		return (ERROR);
	for (; av[len]; len++);
	opt->teams = calloc(len + 1, sizeof(char*));
	for (int i = 0; av[i] && av[i][0] != '-'; i++, h++)
		opt->teams[h] = av[i];
	opt->teams[h] = NULL;
	return (SUCCESS);
}

int clients(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->max_clients = atoi(av[0]);
	return (SUCCESS);
}

int freq(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->freq = atoi(av[0]);
	return (SUCCESS);
}

int usage(char **av, t_opts *opt)
{
	(void)av;
	(void)opt;
	printf(USAGE);
	return (SUCCESS);
}