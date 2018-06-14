/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_team
*/

#include "server.h"
#include "manage_time.h"

size_t places_in_client_team(t_server *server, t_client *owner)
{
	t_client *client = server->clients;
	size_t i = server->opts->max_clients;

	while (client) {
		if (owner->team && client->team &&
		owner->team->id == client->team->id)
			i -= 1;
		client = client->next;
	}
	return (i);
}

int player_in_team(t_server *server, t_team *team)
{
	t_client *client = server->clients;
	size_t i = 0;

	while (client) {
		if (team && client->team && team->id == client->team->id)
			i += 1;
		client = client->next;
	}
	return (i);
}

char *connect_number(t_server *server, t_message *cmd)
{
	char *response;

	cmd->finish_date = time_until_finish(0, server->opts->freq);
	asprintf(&response, "%ld", places_in_client_team(server, cmd->owner));
	return (response);
}

void find_team(t_server *server, t_client *client, const char *name)
{
	t_team **teams = server->opts->teams;

	for (int i = 0 ; teams[i] ; i++) {
		if (strcmp(teams[i]->name, name) == 0 && player_in_team(server, teams[i]) < server->opts->max_clients) {
			client->team = teams[i];
			dprintf(client->socket, "%ld\n", places_in_client_team(server, client));
			dprintf(client->socket, "%d %d\n", server->opts->x, server->opts->y);
			client->last_eat = time_until_finish(LIFE_TIME, server->opts->freq);
			break;
		}
	}
}