/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast
*/

#include "player_actions.h"
#include "manage_time.h"

void send_all(const t_server *server, const t_client *owner, const char *message)
{
	t_client *tmp = server->clients;

	while (tmp) {
		if (owner->player_id != tmp->player_id && tmp->team)
			dprintf(tmp->socket, "%s\n", message);
		tmp = tmp->next;
	}
}

char *broadcast(t_server *server, t_message *cmd)
{
	char *response;

	cmd->finish_date = time_until_finish(BROADCAST_TIME, server->opts->freq);
	asprintf(&cmd->broadcast, "Message %d, %s", 0, &cmd->request[11]);
	asprintf(&response, "ok");
	return (response);
}