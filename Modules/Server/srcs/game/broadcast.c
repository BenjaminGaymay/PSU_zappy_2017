/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast
*/

#include "player_actions.h"
#include "manage_time.h"

void send_all(const t_server *server,
		const t_client *owner, const char *message)
{
	t_client *tmp = server->clients;

	while (tmp) {
		if (owner->player_id != tmp->player_id && tmp->team)
			dprintf(tmp->socket, "%s\n", message);
		tmp = tmp->next;
	}
}

int switch_diagonal_directions(t_server *server, t_pos owner, t_pos pos)
{
	if (owner.y < pos.y && owner.y - pos.y < server->opts->y / 2)
		return (owner.x > pos.x && owner.x - pos.x
			< server->opts->x / 2 ? 8 : 2);
	else
		return (owner.y > pos.y && owner.y - pos.y
			< server->opts->y / 2 ? 6 : 4);
}

int switch_directions(t_server *server, t_pos owner, t_pos pos)
{
	if (owner.x == pos.x && owner.y == pos.y)
		return (0);
	else if (owner.x == pos.x)
		return (owner.y > pos.y && owner.y - pos.y
			< server->opts->y / 2 ? 5 : 1);
	else if (owner.y == pos.y)
		return (owner.x > pos.x && owner.x - pos.x
			< server->opts->x / 2 ? 7 : 3);
	return (switch_diagonal_directions(server, owner, pos));
}

char *broadcast(t_server *server, t_message *cmd)
{
	t_client *tmp = server->clients;
	char *response;
	int result = 0;

	cmd->finish_date = time_until_finish(BROADCAST_TIME,
					server->opts->freq);
	while (tmp) {
		if (cmd->owner->player_id != tmp->player_id && tmp->team) {
			result = switch_directions(server,
				cmd->owner->pos, tmp->pos);
			result = (result + 2 * tmp->look) % 8;
			result = (result == 0 ? 8 : result);
		}
		tmp = tmp->next;
	}
	// asprintf(&cmd->broadcast, "Message %d, %s", 0, &cmd->request[11]);
	asprintf(&response, "ok");
	return (response);
}