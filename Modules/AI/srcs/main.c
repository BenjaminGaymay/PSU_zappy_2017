/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "macro.h"
#include "arguments_ai.h"
#include "server.h"
#include "tools.h"

int main(int ac, char **av)
{
	t_opts_ai opt;

	(void)ac;
	srand(time(NULL));
	manage_commands(av, &opt);
	if (check_commands(&opt) == false)
		return (printf("Bad parameters.\n"), ERROR);
	connect_to_server(&opt);
	// printf("port : %d\nname : %s\nmachine : %s\n", opt.port, opt.name, opt.machine);
	return (0);
}