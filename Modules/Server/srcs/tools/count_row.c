/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <stdlib.h>

size_t count_row(char **array)
{
	size_t lenght = 0;

	if (!array)
		return (0);
	for (size_t i = 0 ; array[i] != NULL ; ++i);
	return (lenght);
}