/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Sfml.hpp"

void Graphical::Sfml::dropStone(const char &id, const float &scale, const size_t &x, const size_t &y)
{
	float elem = scale / 3.0f;
	auto &sprite_2 = _blocks[id];
	float size_2 = sprite_2->getTexture()->getSize().x;
	sprite_2->setScale({elem / size_2, elem / size_2});
	auto pos = getEntityPos(id);
	sprite_2->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_screen.draw(*sprite_2);
}

float Graphical::Sfml::findMapScale(std::vector<std::vector<char>> &map)
{
	/*size_t max_y = map.size(), max_x = map[0].size();
	float height = _window.getSize().y, width = _window.getSize().x;
	float min_window = height > width ? width : height;
	float max_map = max_y > max_x ? max_y : max_x;
	float scale = min_window / max_map;

	return (scale);*/
	size_t max_y = map.size(), max_x = map[0].size();
	float height = _window.getSize().y, width = _window.getSize().x;
	float scale = width / max_x;

	if (max_y * scale > height)
		scale = height / max_y;
	return (scale);
}

void Graphical::Sfml::print_map(std::vector<std::vector<char>> &map)
{
	float scale = findMapScale(map);
	int x = 0, y = static_cast<int>((_window.getSize().y / 2) - (map.size() / 2.0f * scale));

	for (auto &line : map) {
		x = static_cast<int>((_window.getSize().x / 2) - (line.size() / 2.0f * scale));
		for (auto &block : line) {
			if (block == 0) {
				auto &sprite = _blocks[block];
				float size = sprite->getTexture()->getSize().x;
				sprite->setScale({scale / size, scale / size});
				sprite->setPosition(sf::Vector2f(x, y));
				_screen.draw(*sprite);
				dropStone(1, scale, x, y);
				dropStone(2, scale, x, y);
				dropStone(3, scale, x, y);
				dropStone(4, scale, x, y);
				dropStone(5, scale, x, y);
				dropStone(6, scale, x, y);
				dropStone(7, scale, x, y);
				dropStone(8, scale, x, y);
			}
			x += scale;
		}
		y += scale;
	}
}
