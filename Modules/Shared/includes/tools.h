/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tools
*/

#pragma once

bool arr_contains(const char **, const char *);
int index_in_arr(const char **, const char *);
void free_tab(void **);
char **str_to_tab(char *, char *);
void show_tab(char **);

char *lstrip(char *, char *);
char *rstrip(char *, char *);
char char_to_upper(char);
void str_to_upper(char *);
int count_words(char *, char *);
bool is_number(char *);