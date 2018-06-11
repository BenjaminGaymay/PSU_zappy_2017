/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** array_tools
*/

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "macro.h"
#include "tools.h"

bool arr_contains(const char **haystack, const char *needle)
{
	if (!needle)
		return (false);
	for (int i = 0; haystack[i]; i++)
		if (strcmp(needle, haystack[i]) == 0)
			return (true);
	return (false);
}

int index_in_arr(const char **haystack, const char *needle)
{
	for (int i = 0; haystack[i]; i++)
		if (strcmp(needle, haystack[i]) == 0)
			return (i);
	return (ERR_FC);
}

void free_tab(void **tab)
{
	for (int i = 0; tab[i]; i++)
		free(tab[i]);
	free(tab);
}

char **str_to_tab(char *str, char *delimiter)
{
	char **tab = NULL;
	int i = 0;

	tab = calloc(count_words(str, delimiter) + 2, sizeof(char *));
	if (!tab)
		return (FCT_FAILED("malloc"), NULL);
	tab[i] = strtok(str, delimiter);
	while (tab[i] != NULL)
		tab[++i] = strtok(NULL, delimiter);
	return (tab);
}

void show_tab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		printf("%s\n", tab[i]);
}