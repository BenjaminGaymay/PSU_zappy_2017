/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_messages
*/

#include "communication.h"

int add_message_in_list(t_server *server, t_client *client, const char *request)
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
	new->next = NULL;
	if (server->messages)
		last_message->next = new;
	else
		server->messages = new;
	return (last_message = new, SUCCESS);
}

void read_all_messages(t_message *messages)
{
	t_message *tmp = messages;

	while (tmp) {
		printf("Message from client '%ld': '%s'\n", tmp->owner->player_id, tmp->request);
		tmp = tmp->next;
	}
}

void remove_all_messages(t_server *server)
{
	t_message *message = server->messages;

	while (server->messages) {
		message = server->messages->next;
		if (server->messages->request)
			free(server->messages->request);
		if (server->messages->response)
			free(server->messages->response);
		free(server->messages);
		server->messages = message;
	}
	server->messages = NULL;
}