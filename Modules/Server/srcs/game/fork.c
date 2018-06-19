/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** fork
*/

#include "client.h"
#include "manage_time.h"

char *fork_cmd(t_server *server, t_message *cmd)
{
	char *response;

	cmd->finish_date = time_until_finish(EGG_TIME, server->opts->freq);
	return (asprintf(&response, "ok"), response);
}