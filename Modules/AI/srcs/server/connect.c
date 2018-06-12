/*
** EPITECH PROJECT, 2018
** server_zappy ()
** File description:
** connect
*/

#include <stdio.h>
#include "macro.h"
#include "arguments_ai.h"
#include "sockets.h"

int connect_to_server(t_opts_ai *opt)
{
	int fd = create_socket(opt->port, inet_addr("127.0.0.1"), CLIENT);

	if (fd == FD_ERROR)
		return (FCT_FAILED("create_socket"), ERROR);
	return (SUCCESS);
}