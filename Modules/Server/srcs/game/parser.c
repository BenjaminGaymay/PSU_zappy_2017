/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** parser
*/

#include "player_actions.h"

static t_ptr_action *get_ptr_actions(void){
	static t_ptr_action ptr[] = {
		{forward, "Forward"},
		{right, "Right"},
		{left, "Left"},
		{look, "Look"},
		{inventory, "Inventory"},
		// {broadcast, "Broadcast text"},
		{connect_number, "Connect_nbr"},
		// {fork_cmd, "Fork"},
		// {eject, "Eject"},
		// {take_obj, "Take object"},
		// {set_obj, "Set object"},
		// {incantation, "Incantation"},
		{is_graphical, "msz"},
		{NULL, NULL}
	};

	return (ptr);
}

void parse_command(t_server *server, t_message *command)
{
	t_ptr_action *ptr = get_ptr_actions();

	if (command->finish_date != DEFAULT_VALUE || !command->owner || command->owner->occupied)
		return;
	for (int i = 0 ; ptr[i].cmd ; i++) {
		if (strncmp(ptr[i].cmd, command->request, strlen(ptr[i].cmd)) == 0) {
			command->owner->occupied = true;
			command->response = ptr[i].fct(server, command);
			break;
		}
	}
	if (!command->response)
		asprintf(&command->response, "ko");
}