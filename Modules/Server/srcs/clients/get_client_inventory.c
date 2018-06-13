/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** manage_clients
*/

#include "client.h"

char *get_client_inventory(t_client *client)
{
	char *str;
	const t_get_type tab[7] = {{client->inventory.food, "food"},
	{client->inventory.linemate, "linemate"},
	{client->inventory.deraumere, "deraumere"},
	{client->inventory.sibur, "sibur"},
	{client->inventory.mendiane, "mendiane"},
	{client->inventory.phiras, "phiras"},
	{client->inventory.thystame, "thystame"}};

	asprintf(&str, "[");
	for (int i = 0; i < 7;++i) {
		asprintf(&str, "%s%s %ld", str, tab[i].str, tab[i].x);
		if (i < 6)
			asprintf(&str, "%s, ", str);
	}
	asprintf(&str, "%s]", str);
	printf("%s\n", str);
	return (str);
}