/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_client
*/

#include "client.h"
#include "manage_time.h"

char *inventory(t_server *server, t_message *cmd)
{
	char *str;
<<<<<<< HEAD
	const t_get_type tab[7] = {{client->inventory.food, "food"},
	{client->inventory.linemate, "linemate"},
	{client->inventory.deraumere, "deraumere"},
	{client->inventory.sibur, "sibur"},
	{client->inventory.mendiane, "mendiane"},
	{client->inventory.phiras, "phiras"},
	{client->inventory.thystame, "thystame"}};
=======
	const t_get_type tab[7] = {{cmd->owner->inventory.food, "food"},
	{cmd->owner->inventory.linemate, "linemate"},
	{cmd->owner->inventory.deraumere, "deraumere"},
	{cmd->owner->inventory.sibur, "sibur"},
	{cmd->owner->inventory.mendiane, "mendiane"},
	{cmd->owner->inventory.phiras, "phiras"},
	{cmd->owner->inventory.thystame, "thystame"}};
>>>>>>> Server

	cmd->finish_date = time_until_finish(FORWARD_TIME, server->opts->freq);
	asprintf(&str, "[");
	for (int i = 0; i < 7;++i) {
		asprintf(&str, "%s%s %ld", str, tab[i].str, tab[i].x);
		if (i < 6)
			asprintf(&str, "%s, ", str);
	}
	asprintf(&str, "%s]", str);
	return (str);
}