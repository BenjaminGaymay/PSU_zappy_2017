/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** arguments
*/

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "arguments_ai.h"
#include "macro.h"

bool check_commands(t_opts_ai *opt)
{
	return (!(opt->port <= 0 || !opt->name || !opt->machine));
}

static t_args *populate_args(void)
{
	t_args *args = malloc(sizeof(t_args) * (COMMAND_SIZE_AI + 1));

	if (!args)
		return (FCT_FAILED("malloc"), NULL);
	args[0] = (t_args){"-p", &port};
	args[1] = (t_args){"-n", &name};
	args[2] = (t_args){"-h", &machine};
	args[3] = (t_args){"-help", &help};
	args[4] = (t_args){NULL};
	return (args);
}

static void populate_options(t_opts_ai *opt)
{
	opt->port = DEFAULT_VALUE;
	opt->name = NULL;
	opt->machine = NULL;
}

int manage_commands(char **av, t_opts_ai *opt)
{
	t_args *args = populate_args();

	populate_options(opt);
	if (!args)
		return (ERROR);
	for (int i = 1; av[i]; i++)
		for (int j = 0; j < COMMAND_SIZE_AI; j++)
			if (strcmp(av[i], args[j].flag) == 0)
				args[j].function(&av[i+1], opt);
	free(args);
	return (SUCCESS);
}