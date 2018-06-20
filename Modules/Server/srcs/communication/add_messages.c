/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** add_messages
*/

#include "communication.h"

int add_message_in_list(t_server *server, t_client *client,
			const char *request)
{
	static t_message *last_message = NULL;
	t_message *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	new->owner = client;
	new->request = strdup(request);
	if (!new->request)
		return (FCT_FAILED("strdup"), ERROR);
	new->response = NULL;
	new->finish_date = DEFAULT_VALUE;
	new->graphics_message = NULL;
	new->next = NULL;
	if (server->messages)
		last_message->next = new;
	else
		server->messages = new;
	return (last_message = new, SUCCESS);
}

int add_special_response(t_server *server, t_client *client, char *response)
{
	t_message *new = calloc(1, sizeof(*new));

	if (!new)
		return (FCT_FAILED("malloc"), ERROR);
	new->owner = client;
	new->request = NULL;
	new->graphics_message = NULL;
	new->response = response;
	new->finish_date = 0;
	new->next = server->messages;
	server->messages = new;
	return (SUCCESS);
}
