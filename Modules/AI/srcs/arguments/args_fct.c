/*
** EPITECH PROJECT, 2018
** server_zappy ()
** File description:
** args_fct
*/

#include <stdlib.h>
#include "macro.h"
#include "arguments.h"

int help(char **av, t_opts *opt)
{
	(void)opt;
	(void)av;
	printf(USAGE);
	return (SUCCESS);
}

int port(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->port = atoi(av[0]);
	return (SUCCESS);
}

int name(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->name = av[0];
	return (SUCCESS);
}

int machine(char **av, t_opts *opt)
{
	if (!av[0])
		return (ERROR);
	opt->machine = av[0];
	return (SUCCESS);
}