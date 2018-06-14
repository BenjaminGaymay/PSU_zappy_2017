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

void Graphical::Game::dropStone(const char &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite_2 = _sfml->getBlock(id);
	float size_2 = sprite_2->getTexture()->getSize().x;
	sprite_2->setScale({elem / size_2, elem / size_2});
	auto pos = getEntityPos(id);
	sprite_2->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite_2);
}

float Graphical::Game::findMapScale(const Pos &pos)
{
	/*size_t max_y = map.size(), max_x = map[0].size();
	float height = _window.getSize().y, width = _window.getSize().x;
	float min_window = height > width ? width : height;
	float max_map = max_y > max_x ? max_y : max_x;
	float scale = min_window / max_map;

	return (scale);*/
	int max_y = pos.y, max_x = pos.x;
	float height = _sfml->getScreen().getSize().y, width = _sfml->getScreen().getSize().x;
	float scale = width / max_x;

	if (max_y * scale > height)
		scale = height / max_y;
	return (scale);
}

void Graphical::Game::printMap(const std::vector<std::unique_ptr<Case>> &map)
{
	float scale = findMapScale(_map->getSize());
	float marginX = (_sfml->getScreen().getSize().x / 2.0f) - (_map->getSize().x / 2.0f * scale);
	float marginY = (_sfml->getScreen().getSize().y / 2.0f) - (_map->getSize().y / 2.0f * scale);

	for (auto &block : map) {
		auto &sprite = _sfml->getBlock(0);
		float size = sprite->getTexture()->getSize().x;
		sprite->setScale({scale / size, scale / size});
		float x = marginX + (block->getPos().x * scale);
		float y = marginY + (block->getPos().y * scale);
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
}
