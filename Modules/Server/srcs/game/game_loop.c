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

static t_client *player_starving_to_death(t_server *server, t_client *dead_man)
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
			tmp->last_eat = time_until_finish(LIFE_TIME, server->opts->freq);
			tmp = player_starving_to_death(server, tmp);
		} else
			tmp = tmp->next;
	}
}

int game_loop(t_server *server)
{
	while (1) {
		if (manage_sockets(server) == ERROR)
			return (ERROR);
		lost_lives(server, server->clients);
		read_all_messages(server, server->messages);
		send_responses(server, server->messages);
		remove_finished_actions(server);
		spawn_object(server);
	}
	return (SUCCESS);
}