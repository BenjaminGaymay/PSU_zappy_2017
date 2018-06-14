/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_client
*/

#include "client.h"
#include "manage_time.h"

char *take_obj(t_server *server, t_message *cmd)
{
	char *str;
	t_change_map tab[7] = {
	{&cmd->owner->inventory.food, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].food, "food"},
	{&cmd->owner->inventory.linemate, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].linemate, "linemate"},
	{&cmd->owner->inventory.deraumere, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].deraumere, "deraumere"},
	{&cmd->owner->inventory.sibur, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].sibur, "sibur"},
	{&cmd->owner->inventory.mendiane, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].mendiane, "mendiane"},
	{&cmd->owner->inventory.phiras, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].phiras, "phiras"},
	{&cmd->owner->inventory.thystame, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].thystame, "thystame"}};

	if (strlen(cmd->request) <= 5)
		return (asprintf(&str, "ko"), str);
	cmd->request = &cmd->request[5];
	for (int i = 0; i < 7; ++i)
		if (strcmp(cmd->request, tab[i].str) == 0 && *(tab[i].x) > 0) {
			*(tab[i].inv) += 1;
			*(tab[i].x) -= 1;
			return (asprintf(&str, "ok"), str);
		}
	return (asprintf(&str, "ko"), str);
}

char *set_obj(t_server *server, t_message *cmd)
{
	char *str;
	t_change_map tab[7] = {
	{&cmd->owner->inventory.food, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].food, "food"},
	{&cmd->owner->inventory.linemate, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].linemate, "linemate"},
	{&cmd->owner->inventory.deraumere, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].deraumere, "deraumere"},
	{&cmd->owner->inventory.sibur, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].sibur, "sibur"},
	{&cmd->owner->inventory.mendiane, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].mendiane, "mendiane"},
	{&cmd->owner->inventory.phiras, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].phiras, "phiras"},
	{&cmd->owner->inventory.thystame, &server->map[cmd->owner->pos.y][cmd->owner->pos.x].thystame, "thystame"}};

	if (strlen(cmd->request) <= 4)
		return (asprintf(&str, "ko"), str);
	cmd->request = &cmd->request[4];
	for (int i = 0; i < 7; ++i)
		if (strcmp(cmd->request, tab[i].str) == 0 && *(tab[i].inv) > 0) {
			*(tab[i].inv) -= 1;
			*(tab[i].x) += 1;
			return (asprintf(&str, "ok"), str);
		}
	return (asprintf(&str, "ko"), str);
}