/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Game.hpp"

Graphical::Pos Graphical::Game::getEntityPos(const char &block)
{
	static std::map<char, Graphical::Pos> map = {
			{1, {0, 0}},
			{2, {1, 0}},
			{3, {2, 0}},
			{4, {0, 1}},
			{5, {2, 2}},
			{6, {2, 1}},
			{7, {0, 2}},
			{8, {1, 2}},
	};
	return map[block];
};

void Graphical::Game::dropStone(const char &id, const float &scale, const size_t &x, const size_t &y)
{
	float elem = scale / 3.0f;
	auto &sprite_2 = _sfml->getBlock(id);
	float size_2 = sprite_2->getTexture()->getSize().x;
	sprite_2->setScale({elem / size_2, elem / size_2});
	auto pos = getEntityPos(id);
	sprite_2->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite_2);
}

float Graphical::Game::findMapScale(std::vector<std::vector<char>> &map)
{
	/*size_t max_y = map.size(), max_x = map[0].size();
	float height = _window.getSize().y, width = _window.getSize().x;
	float min_window = height > width ? width : height;
	float max_map = max_y > max_x ? max_y : max_x;
	float scale = min_window / max_map;

	return (scale);*/
	size_t max_y = map.size(), max_x = map[0].size();
	float height = _sfml->getScreen().getSize().y, width = _sfml->getScreen().getSize().x;
	float scale = width / max_x;

	if (max_y * scale > height)
		scale = height / max_y;
	return (scale);
}

void Graphical::Game::printMap(std::vector<std::vector<char>> &map)
{
	float scale = findMapScale(map);
	int x = 0, y = static_cast<int>((_sfml->getScreen().getSize().y / 2.0f) - (map.size() / 2.0f * scale));

	for (auto &line : map) {
		x = static_cast<int>((_sfml->getScreen().getSize().x / 2.0f) - (line.size() / 2.0f * scale));
		for (auto &block : line) {
			if (block == 0) {
				auto &sprite = _sfml->getBlock(block);
				float size = sprite->getTexture()->getSize().x;
				sprite->setScale({scale / size, scale / size});
				sprite->setPosition(sf::Vector2f(x, y));
				_sfml->getScreen().draw(*sprite);
				if (_filters[2]) {
					dropStone(1, scale, x, y);
					dropStone(2, scale, x, y);
					dropStone(3, scale, x, y);
					dropStone(4, scale, x, y);
					dropStone(5, scale, x, y);
					dropStone(6, scale, x, y);
				}
				if (_filters[7])
					dropStone(7, scale, x, y);
				if (_filters[8])
					dropStone(8, scale, x, y);
			}
			x += scale;
		}
		y += scale;
	}
}
