/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** response
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "ai.h"
#include "macro.h"

int look_around(t_ai *ai, char *s)
{
	printf("salut\n");
	return (SUCCESS);
}

int inventory(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	return (SUCCESS);
}

int pass(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	return (SUCCESS);
}

int broadcast(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	return (SUCCESS);
}

static int process_response(t_ai *ai, char *tmp)
{
	static const t_response response[] = {
		{"Look", look_around},
		{"Inventory", inventory},
		{"Turn", pass},
		{"Take", pass},
		{"Broadcast", broadcast},
		{NULL}
	};
	char *data = get_nth_data(ai->list, listlen(ai->list) - 1);

	if (!data)
		return (ERROR);
	for (int i = 0; response[i].msg; i++) {
		if (strncmp(data, response[i].msg, strlen(response[i].msg)) == 0) {
			response[i].fct(ai, tmp);
			delete_node(&ai->list, 0);
			break;
		}
	}
	return (SUCCESS);
}

static int check_response_serv(t_ai *ai)
{
	static char buf[4096];
	int size = read(ai->fd, buf, 4096);

	if (size == ERR_FC)
		return (ERROR);
	for (char *tmp = strtok(buf, "\n"); tmp; tmp = strtok(NULL, "\n"))
		process_response(ai, tmp);
	return (SUCCESS);
}

int wait_for_response(t_ai *ai)
{
	static fd_set fd_read;
	struct timeval tv = {0, 50};

	FD_ZERO(&fd_read);
	FD_SET(ai->fd, &fd_read);
	if (select(ai->fd + 1, &fd_read, NULL, NULL, &tv) == -1)
		return (FCT_FAILED("select"), ERROR);
	if (FD_ISSET(ai->fd, &fd_read))
		return (check_response_serv(ai));
	return (SUCCESS);
}