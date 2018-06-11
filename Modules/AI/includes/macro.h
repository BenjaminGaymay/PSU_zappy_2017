/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** macro
*/

#pragma once

#include <stdio.h>

#define ERROR 84
#define SUCCESS 0
#define FAILURE 1
#define ERR_FC -1
#define COMMAND_SIZE 4
#define DEFAULT_VALUE -1
#define USAGE "USAGE: ./zappy_ai -p port -n name -h machine\
\n\tport\tis the port number\
\n\tname\tis the name of the team\
\n\tmachine\tis the name of the machine; localhost by default\n"

#define FCT_FAILED(s) fprintf(stderr, "Error: %s failed.\n", s)
