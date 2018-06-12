/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** string_tools
*/

#include <string.h>
#include "macro.h"

char *lstrip(char *s, char *c)
{
	int i = 0;
	(void)c;
	if (!s)
		return (NULL);
	while (s[i] && strchr(c, s[i]))
		++i;
	s = &s[i];
	return (s);
}

char *rstrip(char *s, char *c)
{
	int i;

	(void)c;
	if (!s)
		return (NULL);
	i = strlen(s) - 1;
	while (i > 0 && strchr(c, s[i]))
		--i;
	s[i + 1] = '\0';
	return (s);
}

char char_to_upper(char c)
{
	return (c >= 'a' && c <= 'z' ? c - 32 : c);
}

void str_to_upper(char *str)
{
	if (!str)
		return;
	for (; *str != '\0'; str++)
		*str = char_to_upper(*str);
}

int count_words(char *str, char *delimiter)
{
	int state = 0;
	int count = 0;

	while (*str) {
		if (strchr(delimiter, *str))
			state = 0;
		else if (state == 0) {
			state = 1;
			++count;
		}
		++str;
	}
	return (count);
}