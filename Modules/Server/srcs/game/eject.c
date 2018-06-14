/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_client
*/

#include "client.h"
#include "manage_time.h"

static void move_eject(t_opts *opts, t_client *client, size_t look)
{
	switch (look) {
		case 0:
		client->pos.y -= (client->pos.y <= 0 ? -opts->y + 1 : 1);
		break;
		case 1:
		client->pos.x += (client->pos.x >= opts->x - 1? -opts->x + 1 : 1);
		break;
		case 2:
		client->pos.y += (client->pos.y >= opts->y - 1? -opts->y + 1 : 1);
		break;
		case 3:
		client->pos.x -= (client->pos.x <= 0 ? -opts->x + 1 : 1);
		break;
	}
}

static int add_eject_response(t_server *server, t_client *client, size_t look)
{
	t_message *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	new->owner = client;
	new->request = NULL;
	asprintf(&new->response, "Eject: %ld", look);
	new->broadcast = NULL;
	new->finish_date = 0;
	new->send = false;
	new->next = server->messages;
	server->messages = new;
	return (SUCCESS);
}

char *eject(t_server *server, t_message *cmd)
{
	char *str;
	t_client *client = server->clients;

	cmd->finish_date = time_until_finish(EJECT_TIME, server->opts->freq);
	while (client) {
		if (client->player_id != cmd->owner->player_id
		&& client->pos.y == cmd->owner->pos.y
		&& client->pos.x == cmd->owner->pos.x) {
			move_eject(server->opts, client, cmd->owner->look);
			add_eject_response(server, client, cmd->owner->look);
		}
		client = client->next;
	}
	return (asprintf(&str, "ok"), str);
}