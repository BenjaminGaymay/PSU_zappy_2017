/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** game_loop
*/

#include "communication.h"
#include "manage_time.h"
#include "client.h"
#include "game.h"

static t_client *player_starving_to_death(t_server *server,
					t_client *dead_man)
{
	t_client *save;

	if (dead_man->team && dead_man->inventory.food == 0) {
		save = dead_man->next;
		remove_client(server, dead_man, true);
		return (save);
	}
	return (dead_man->next);
}


static void lost_lives(t_server* server, t_client *clients)
{
	t_client *tmp = clients;

	while (tmp) {
		if (is_finish(tmp->last_eat)) {
			tmp->inventory.food -= 1;
			tmp->last_eat = time_until_finish(
				LIFE_TIME, server->opts->freq);
			tmp = player_starving_to_death(server, tmp);
		} else
			tmp = tmp->next;
	}
}

static void check_incantations_state(t_server *server, t_message *messages)
{
	t_message *tmp = messages;

	while (tmp) {
		if (tmp->request && strcmp(tmp->request, "Incantation") == 0 &&
		!tmp->response && tmp->owner && is_finish(tmp->finish_date)) {
			if (server->map[tmp->owner->pos.y][tmp->owner->pos.x].incantation &&
			is_inventory_complete(server, tmp->owner)) {
				asprintf(&tmp->response, "Current level: %ld",
				++tmp->owner->level);
				reset_inventory(tmp->owner);
				if (tmp->owner->level == MAX_LEVEL)
					server->continue_game = false;
			} else
				asprintf(&tmp->response, "ko");
		}
		tmp = tmp->next;
	}
}

int game_loop(t_server *server)
{
	while (server->continue_game) {
		if (manage_sockets(server) == ERROR)
			return (ERROR);
		lost_lives(server, server->clients);
		read_all_messages(server, server->messages);
		check_incantations_state(server, server->messages);
		send_responses(server, server->messages);
		spawn_object(server, false);
	}
	return (SUCCESS);
}