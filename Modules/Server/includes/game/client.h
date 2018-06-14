/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client
*/

#pragma once

#include "server.h"

int add_client(t_server *);
void remove_client(t_server *, t_client *, bool);
void remove_all_clients(t_client *);
int player_in_team(t_server *, t_team *);
size_t places_in_client_team(t_server *, t_client *);
size_t get_clients_number(t_client *);
void find_team(t_server *, t_client *, const char *);