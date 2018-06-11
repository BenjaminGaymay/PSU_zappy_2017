
/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** macro
*/

#pragma once

#include <stdio.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR 84
#define FAILED 1
#define COMMAND_SIZE_SERVER 7
#define COMMAND_SIZE_AI 4
#define DEFAULT_VALUE -1
#define ERR_FC -1
#define FD_ERROR -1

#define FCT_FAILED(s) fprintf(stderr, "Error: %s failed.\n", s)

#define USAGE_SERVER "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c clientsNb -f freq\
	\n\tport\tis the port number\
	\n\twidth\tis the width of the world\
	\n\theight\tis the height of the world\
	\n\tnameX\tis the name of the team X\
	\n\tclientsNb\tis the number of authorized clients per team\
	\n\tfreq\tis the reciprocal of time unit for execution of actions\n"

#define USAGE_AI "USAGE: ./zappy_ai -p port -n name -h machine\
	\n\tport\tis the port number\
	\n\tname\tis the name of the team\
	\n\tmachine\tis the name of the machine; localhost by default\n"
