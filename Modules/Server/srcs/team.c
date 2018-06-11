/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <string.h>
#include <glob.h>
#include "server.h"

bool init_team(t_server *server)
{
	size_t lenght = count_row(server->opts->teams);
	int team[lenght];

	if (lenght == 0)
		return (false);
	for (size_t i = 0 ; i < lenght ; ++i)
		team[i] = 0;
	return (true);
}

bool add_team_member(t_server *server, char *team_name)
{
	size_t limit = count_row(server->opts->teams);

	for (size_t id = 0; id < limit ; ++id) {
		if (strcmp(server->opts->teams[id], team_name) == 0) {
			server->team[id] += 1;
			return (true);
		}
	}
	return (false);
}

bool remove_team_member(t_server *server, char *team_name)
{
	size_t limit = count_row(server->opts->teams);

	for (size_t id = 0; id < limit ; ++id) {
		if (strcmp(server->opts->teams[id], team_name) == 0 && server->team[id] > 0) {
			server->team[id] -= 1;
			return (true);
		}
	}
	return (false);
}