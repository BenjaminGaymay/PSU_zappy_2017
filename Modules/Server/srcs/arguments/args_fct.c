/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "tools.h"
#include "arguments_server.h"

int port(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) <= 0)
		return (NOT_NUMBER("port"), ERROR);
	opt->port = atoi(av[0]);
	return (SUCCESS);
}

int width(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) <= 0)
		return (NOT_NUMBER("width"), ERROR);
	opt->x = atoi(av[0]);
	return (SUCCESS);
}

int height(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) <= 0)
		return (NOT_NUMBER("height"), ERROR);
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
	if (!is_number(av[0]) || atoi(av[0]) <= 0)
		return (NOT_NUMBER("number of clients"),
			ERROR);
	opt->max_clients = atoi(av[0]);
	return (SUCCESS);
}

int freq(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	if (!is_number(av[0]) || atoi(av[0]) <= 0)
		return (NOT_NUMBER("frequency"),
			ERROR);
	opt->freq = atoi(av[0]);
	return (SUCCESS);
}

int usage(char **av, t_opts *opt)
{
	(void)av;
	(void)opt;
	printf(USAGE_SERVER);
	return (SUCCESS);
}