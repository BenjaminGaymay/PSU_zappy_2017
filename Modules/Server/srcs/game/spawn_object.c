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

void add_in_map(t_server *server, int i)
{
	t_pos pos = {rand() % server->opts->x, rand() % server->opts->y};
	size_t **tab;
	t_inventory aCase = server->map[pos.y][pos.x];
	char *msg = NULL;

	tab = malloc(sizeof(size_t) * 8);
	tab[0] = &server->map[pos.y][pos.x].food;
	tab[1] = &server->map[pos.y][pos.x].linemate;
	tab[2] = &server->map[pos.y][pos.x].deraumere;
	tab[3] = &server->map[pos.y][pos.x].sibur;
	tab[4] = &server->map[pos.y][pos.x].mendiane;
	tab[5] = &server->map[pos.y][pos.x].phiras;
	tab[6] = &server->map[pos.y][pos.x].thystame;
	*(tab[i]) += 1;
	asprintf(&msg, "bct %d %d %ld %ld %ld %ld %ld %ld %ld", pos.x, pos.y,
			 aCase.food, aCase.linemate, aCase.deraumere, aCase.sibur,
			 aCase.mendiane, aCase.phiras, aCase.thystame);
	send_to_graphics(server, msg);
	free(tab);
}

t_time *time_creator(t_server *server)
{
	static t_time *timing;

	timing = malloc(sizeof(t_time) * 7);
	timing[0] = (t_time){time_until_finish(SPAWN_FOOD,
		server->opts->freq), SPAWN_FOOD};
	timing[1] = (t_time){time_until_finish(SPAWN_LINEMATE,
		server->opts->freq), SPAWN_LINEMATE};
	timing[2] = (t_time){time_until_finish(SPAWN_DERAUMERE,
		server->opts->freq), SPAWN_DERAUMERE};
	timing[3] = (t_time){time_until_finish(SPAWN_SIBUR,
		server->opts->freq), SPAWN_SIBUR};
	timing[4] = (t_time){time_until_finish(SPAWN_MENDIANE,
		server->opts->freq), SPAWN_MENDIANE};
	timing[5] = (t_time){time_until_finish(SPAWN_PHIRAS,
		server->opts->freq), SPAWN_PHIRAS};
	timing[6] = (t_time){time_until_finish(SPAWN_THYSTAME,
		server->opts->freq), SPAWN_THYSTAME};
	return (timing);
}

void spawn_object(t_server *server)
{
	static t_time *timing;
	static int i = 0;

	if (i == 0) {
		timing = time_creator(server);
		i = 1;
	}
	for (int i = 0; i < 7; ++i) {
		if (is_finish(timing[i].time)) {
			timing[i].time = time_until_finish(
			timing[i].loop_time, server->opts->freq);
			add_in_map(server, i);
		}
	}
}