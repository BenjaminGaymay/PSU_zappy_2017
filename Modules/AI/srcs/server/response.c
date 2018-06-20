/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** response
*/

#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "ai.h"
#include "macro.h"
#include "commands.h"

int look_around(t_ai *ai, char *s)
{
	char **tab = get_data_from_look(s);
	int dir = rand() % 2;

	if (!tab)
		return (FAILURE);
	ai->inv[EL_PLAYER] = count_substr(tab[0], "player");
	if (strcmp(tab[0], "player") == 0)
		ai->state = dir == 0 ? AI_MOVE : AI_TURN;
	else
		ai->state = AI_TAKE;
	free_tab(tab);
	if (ai->look)
		free(ai->look);
	ai->look = strdup(s);
	return (SUCCESS);
}

static void put_in_inventory(t_ai *ai, char **tmp)
{
	static const t_action action[] = {
		{"linemate", EL_LINEMATE},
		{"deraumere", EL_DERAUMERE},
		{"mendiane", EL_MENDIANE},
		{"phiras", EL_PHIRAS},
		{"sibur", EL_SIBUR},
		{"thystame", EL_THYSTAME},
		{"player", EL_PLAYER},
		{NULL}
	};

	for (int j = 0; action[j].str; j++) {
		if (strcmp(action[j].str, tmp[0]) == 0) {
			ai->inv[action[j].elem] = atoi(tmp[1]);
			break;
		}
	}
}

static void parse_inventory(t_ai *ai, char *s)
{
	char **tab = str_to_tab(s, ",");
	char **tmp = NULL;

	if (!tab)
		return;
	for (int i = 0; tab[i]; i++) {
		tab[i] = lstrip_m(tab[i], "[ ");
		tmp = str_to_tab(tab[i], " ");
		put_in_inventory(ai, tmp);
		free_tab(tmp);
	}
	free_tab(tab);
}

int inventory(t_ai *ai, char *s)
{
	parse_inventory(ai, s);
	for (int i = 0; i < INVENT_SIZE; i++) {
		printf("%ld  ", ai->inv[i]);
	}
	printf("\n");
	return (SUCCESS);
}

int pass(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	printf("%s\n", s);
	return (SUCCESS);
}

int broadcast(t_ai *ai, char *s)
{
	(void)ai;
	(void)s;
	printf("RES : %s\n", s);
	return (SUCCESS);
}

int forward(t_ai *ai, char *s)
{
	char **tab = NULL;
	char **tmp = NULL;

	printf("RES : %s\n", s);
	if (strcmp(s, "ok") != 0 && !ai->look)
		return (ERROR);
	tab = get_data_from_look(ai->look);
	tmp = str_to_tab(tab[0], " ");
	for (int i = 0; tmp[i] && strcmp(tmp[i], "player") == 0; i++)
	if (!tmp[i])
		return (free_tab(tab), free_tab(tmp), ERROR);
	ai->state = AI_TAKE;
	free_tab(tmp);
	return (SUCCESS);
}

int turn(t_ai *ai, char *s)
{
	printf("RES : %s\n", s);

	if (strcmp(s, "ok") != 0)
		return (ERROR);
	ai->state = AI_MOVE;
	return (SUCCESS);
}

static int process_response(t_ai *ai, char *str)
{
	static const t_response response[] = {
		{"Look", look_around},
		{"Inventory", inventory},
		{"Turn", turn},
		{"Take", pass},
		{"Broadcast", broadcast},
		{"Forward", forward},
		{NULL}
	};
	char *data = get_nth_data(ai->list, listlen(ai->list) - 1);

	if (strcmp(str, "dead") == 0)
		return (ai->run = false, SUCCESS);
	if (!data)
		return (ERROR);
	for (int i = 0; response[i].msg; i++) {
		if (strncmp(data, response[i].msg, strlen(response[i].msg)) == 0) {
			response[i].fct(ai, str);
			printf("[!] Delete command\n");
			delete_node(&ai->list, listlen(ai->list) - 1);
			break;
		}
	}
	return (SUCCESS);
}

static int check_response_serv(t_ai *ai)
{
	static char buf[4096];
	int size = read(ai->fd, buf, 4096);
	char **tab = NULL;

	if (size == ERR_FC)
		return (ERROR);
	buf[size] = '\0';
	tab = str_to_tab(buf, "\n");
	for (int i = 0; tab[i]; i++)
		process_response(ai, tab[i]);
	free_tab(tab);
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