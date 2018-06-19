/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_messages
*/

#include "communication.h"
#include "manage_time.h"

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
	new->finish_date = DEFAULT_VALUE;
	new->send = false;
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
	new->response = response;
	new->finish_date = 0;
	new->send = false;
	new->next = server->messages;
	server->messages = new;
	return (SUCCESS);
}

void read_all_messages(t_server *server, t_message *messages)
{
	t_message *tmp = messages;

	while (tmp) {
		parse_command(server, tmp);
		tmp = tmp->next;
	}
}

void remove_messages(t_server *server, t_message *message)
{
	if (message == server->messages)
		server->messages = message->next;
	if (message->request && message->owner) {
		message->owner->request_number -= 1;
		message->owner->occupied = false;
	}
	free(message->request);
	free(message->response);
	free(message);
}

void remove_finished_actions(t_server *server)
{
	t_message *action = server->messages;
	t_message *tmp = server->messages;

	while (action) {
		if (action->finish_date != DEFAULT_VALUE &&
				is_finish(action->finish_date)) {
			tmp = action->next;
			remove_messages(server, action);
			action = tmp;
		} else
			action = action->next;
	}
}

void send_responses(t_message *responses)
{
	t_message *tmp = responses;

	while (tmp) {
		if (tmp->response && !tmp->send && tmp->owner) {
			dprintf(tmp->owner->socket, "%s\n", tmp->response);
			tmp->send = true;
		}
		tmp = tmp->next;
	}
}

void remove_all_messages(t_server *server)
{
	t_message *message = server->messages;

	while (server->messages) {
		message = server->messages->next;
		if (server->messages->request) {
			server->messages->owner->request_number -= 1;
			free(server->messages->request);
		}
		if (server->messages->response)
			free(server->messages->response);
		free(server->messages);
		server->messages = message;
	}
	server->messages = NULL;
}