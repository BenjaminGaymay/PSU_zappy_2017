/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_team
*/

#include <communication.h>
#include "eggs.h"
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

bool find_free_egg(t_server *server, t_team *team)
{
	t_egg *tmp = server->eggs;

	while (tmp) {
		if (team->id == tmp->team->id && is_finish(tmp->finish_date)) {
			remove_egg(server, tmp);
			return (true);
		}
		tmp = tmp->next;
	}
	return (false);
}

void find_team(t_server *server, t_client *client, const char *name)
{
	t_team **teams = server->opts->teams;
	int nb_players;

	for (int i = 0 ; teams[i] ; i++) {
		nb_players = player_in_team(server, teams[i]);
		if (strcmp(teams[i]->name, name) == 0 &&
		nb_players < server->opts->max_clients) {
			if (!find_free_egg(server, teams[i]) &&
			nb_players != 0)
				break;
			client->team = teams[i];
			dprintf(client->socket, "%ld\n",
				places_in_client_team(server, client));
			dprintf(client->socket, "%d %d\n",
				server->opts->x, server->opts->y);
			client->last_eat = time_until_finish(LIFE_TIME,
				server->opts->freq);
			char *msg = NULL;
			asprintf(&msg, "pnw %li %i %i %li %li %s", client->player_id, client->pos.x, client->pos.y, client->look, client->level, client->team->name);
			send_to_graphics(server, msg);
			return;
		}
	}
	add_special_response(server, client, strdup("ko"));
}