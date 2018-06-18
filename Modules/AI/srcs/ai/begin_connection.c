/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** begin_connection
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "macro.h"
#include "ai.h"

static int try_connect(char *buf)
{
	int left_client = atoi(buf);

	if (left_client <= 0)
		return (fprintf(stderr, "Can't connect: too many clients."), ERROR);
	return (SUCCESS);
}

static int receipt_infos(t_ai *ai)
{
	char buf[256];
	char **tmp;
	int size = read(ai->fd, buf, 256);

	if (size > 0) {
		tmp = str_to_tab(buf, "\n");
		if (try_connect(tmp[0]) == ERROR)
			return (ERROR);
		tmp = str_to_tab(tmp[1], " ");
		ai->opts->dim.x = atoi(tmp[0]);
		ai->opts->dim.y = atoi(tmp[1]);
		return (SUCCESS);
	}
	return (ERROR);
}

int receipt_welcome(t_ai *ai)
{
	char buf[256];
	int size = read(ai->fd, buf, 256);
	if (size > 0) {
		buf[size] = '\0';
		printf("%s\n", buf);
	}
	dprintf(ai->fd, "%s\n", ai->opts->name);
	return (receipt_infos(ai));
}