/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** client
*/

#pragma once

#include "server.h"

int add_client(t_server *);
void remove_client(t_server *, t_client *);
void remove_all_clients(t_client *);
size_t get_clients_number(t_client *);