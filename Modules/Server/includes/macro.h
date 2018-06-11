/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** macro
*/

#pragma once

#include <stdio.h>

#define SUCCESS 0
#define ERROR 84
#define FAILED 1
#define COMMAND_SIZE 7
#define DEFAULT_VALUE -1

#define FCT_FAILED(s) fprintf(stderr, "Error: %s failed.\n", s)

#define USAGE "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\
	\n\tport\tis the port number\
	\n\twidth\tis the width of the world\
	\n\theight\tis the height of the world\
	\n\tnameX\tis the name of the team X\
	\n\tclientsNb\tis the number of authorized clients per team\
	\n\tfreq\tis the reciprocal of time unit for execution of actions\n"
