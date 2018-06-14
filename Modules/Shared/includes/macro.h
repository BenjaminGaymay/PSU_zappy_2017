
/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** macro
*/

#pragma once

#ifndef _GNU_SOURCE /* default defined on c++ */
#define _GNU_SOURCE
#endif

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
#define NOT_NUMBER(n) fprintf(stderr, "Error: %s must be a valid number.\n", n)

#define USAGE_SERVER "USAGE: ./zappy_server -p port -x width -y \
	height -n name1 name2 ... -c clientsNb -f freq\
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

#define LOOK_TIME 7
#define FORWARD_TIME 7
#define RIGHT_TIME 7
#define LEFT_TIME 7
#define BROADCAST_TIME 7
#define INVENTORY_TIME 1
#define LIFE_TIME 126
#define TAKE_TIME 7
#define SET_TIME 7
#define EJECT_TIME 7

