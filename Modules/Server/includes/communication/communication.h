/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** communication
*/

#pragma once

#include "server.h"
#include "client.h"

int add_message_in_list(t_server *, t_client *, const char *);
int add_special_response(t_server *, t_client *, char *);
void remove_finished_actions(t_server *);
void read_all_messages(t_server *, t_message *);
void send_responses(const t_server *, t_message *);
void send_all(const t_server *, const t_client *, const char *);
void remove_messages(t_server *, t_message *);
void remove_all_messages(t_server *);
void parse_command(t_server *, t_message *);
void unlink_client_messages(t_server *, t_client *);
void send_to_graphics(t_server *server, char *msg);