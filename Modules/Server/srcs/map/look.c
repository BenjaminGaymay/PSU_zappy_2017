/*
** EPITECH PROJECT, 2018
** zappy_tmp
** File description:
** args_fct
*/

#include "macro.h"
#include "server.h"

static char *(*fct[])(t_server, char *, t_pos pos) = {
	look_top,
	look_right,
	look_bot,
	look_left
};

char *look_top(t_server server, char *str, t_pos pos)
{
	for (int i = 0; i < 4; ++i) {
		if (pos.y - i < 0)
			pos.y += server.opts->y;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_top_bot(server, str, (t_pos){j - 2 * i / 2 + pos.x, -i + pos.y});
		}
	}
	return (str);
}

char *look_right(t_server server, char *str, t_pos pos)
{
	for (int i = 0; i < 4; ++i) {
		if (i + pos.x >= server.opts->x)
			pos.x -= server.opts->x;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_left_right(server, str, (t_pos){i + pos.x, j - 2 * i / 2 + pos.y});
		}
	}
	return (str);
}

char *look_bot(t_server server, char *str, t_pos pos)
{
	for (int i = 0; i < 4; ++i) {
		if (i + pos.y >= server.opts->y)
			pos.y -= server.opts->y;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_top_bot(server, str, (t_pos){j - 2 * i / 2 + pos.x, i + pos.y});
		}
	}
	return (str);
}

char *look_left(t_server server, char *str, t_pos pos)
{
	for (int i = 0; i < 4; ++i) {
		if (pos.x - i < 0)
			pos.x += server.opts->x;
		for (int j = 0; j < (2 * i + 1); ++j) {
			str = get_map_objects_left_right(server, str, (t_pos){-i + pos.x, j - 2 * i / 2 + pos.y});
		}
	}
	return (str);
}

char *look(t_server server)
{
	char *str;
	t_pos pos = {0, 0};
	int direction = 0;

	asprintf(&str, "[");
	printf("top\n");
	str = (*fct[direction])(server, str, pos);
	// printf("right\n");
	// direction = 1;
	// str = (*fct[direction])(server, str, pos);
	// printf("bot\n");
	// direction = 2;
	// str = (*fct[direction])(server, str, pos);
	// printf("left\n");
	// direction = 3;
	// str = (*fct[direction])(server, str, pos);

	asprintf(&str, "%s]", str);
	printf("%s\n", str);
	return (str);
}
