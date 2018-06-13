/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_team
*/

#include "server.h"
#include "manage_time.h"

char *connect_number(t_server *server, t_message *cmd)
{
	t_client *client = server->clients;
	char *response;
	size_t i = 0;

	cmd->finish_date = time_until_finish(0, server->opts->freq);
	while (client) {
		if (cmd->owner->team_id == client->team_id)
			i += 1;
		client = client->next;
	}
	asprintf(&response, "%ld", i);
	return (response);
}