/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** communication
*/

#pragma once

#include "server.h"

int add_message_in_list(t_server *, t_client *, const char *);
void read_all_messages(t_message *);
void remove_all_messages(t_server *);