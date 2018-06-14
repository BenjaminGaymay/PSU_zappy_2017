/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_team
*/

#include "server.h"
#include "manage_time.h"

size_t player_in_team(t_server *server, t_client *owner)
{
	t_client *client = server->clients;
	size_t i = server->opts->max_clients;

	while (client) {
		if (owner->team_id == client->team_id)
			i -= 1;
		client = client->next;
	}
	return (i);
}

char *connect_number(t_server *server, t_message *cmd)
{
	char *response;

	cmd->finish_date = time_until_finish(0, server->opts->freq);
	asprintf(&response, "%ld", player_in_team(server, cmd->owner));
	return (response);
}
