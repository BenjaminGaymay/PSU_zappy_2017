/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include <stdlib.h>
#include "macro.h"
#include "arguments.h"

int port(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->port = atoi(av[0]);
	if (opt->port <= 0)
		return (fprintf(stderr, "Error: port must be positif.\n"), ERROR);
	return SUCCESS;
}

int width(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->x = atoi(av[0]);
	return SUCCESS;
}

int height(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->y = atoi(av[0]);
	return SUCCESS;
}

int name(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->teams = NULL;
	return SUCCESS;
}

int clients(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->max_clients = atoi(av[0]);
	return SUCCESS;
}

int freq(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->freq = atoi(av[0]);
	return SUCCESS;
}
