/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main
*/

#include <stdio.h>
#include "macro.h"
#include "arguments.h"

int main(int ac, char **av)
{
	t_opts opt;

	manage_commands(av, &opt);
	if (check_commands(&opt) == false)
		return (ERROR);
	printf("port : %d\nname : %s\nmachine : %s\n", opt.port, opt.name, opt.machine);
	return (0);
}