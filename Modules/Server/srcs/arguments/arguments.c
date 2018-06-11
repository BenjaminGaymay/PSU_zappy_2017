/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** arguments
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "arguments.h"

static t_args *populate_args(void)
{
	t_args *args = malloc(sizeof(t_args) * (COMMAND_SIZE + 1));

	if (!args)
		return (FCT_FAILED("malloc"), NULL);
	args[0] = (t_args){"-p", &port};
	args[1] = (t_args){"-x", &width};
	args[2] = (t_args){"-y", &height};
	args[3] = (t_args){"-n", &name};
	args[4] = (t_args){"-c", &clients};
	args[5] = (t_args){"-f", &freq};
	args[6] = (t_args){"-help", &usage};
	args[7] = (t_args){NULL};
	return args;
}

static void populate_opt(t_opts *opt)
{
	opt->port = DEFAULT_VALUE;
	opt->x = DEFAULT_VALUE;
	opt->y = DEFAULT_VALUE;
	opt->teams = NULL;
	opt->max_clients = DEFAULT_VALUE;
	opt->freq = 100;
}

int manage_command(int ac, char **av, t_opts *opts)
{
	t_args *args = populate_args();
	populate_opt(opts);

	if (!args)
		return (ERROR);
	for (int j = 1; j < ac; j++)
		for (int i = 0; i < COMMAND_SIZE; i++)
			if (strcmp(av[j], args[i].flag) == 0)
				args[i].function(&av[j + 1], opts);
	free(args);
	return (SUCCESS);
}