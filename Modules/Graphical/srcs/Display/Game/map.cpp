/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Core.hpp"

Graphical::Pos Graphical::Core::getEntityPos(const int &block)
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

void Graphical::Core::dropStone(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite_2 = _sfml->getBlock(id);
	float size_2 = sprite_2->getTexture()->getSize().x;
	sprite_2->setScale({elem / size_2, elem / size_2});
	auto pos = getEntityPos(id);
	sprite_2->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite_2);
}

float Graphical::Core::findMapScale(const Pos &pos)
{
	int max_y = pos.y, max_x = pos.x;
	float height = _sfml->getScreen().getSize().y, width = _sfml->getScreen().getSize().x;
	float scale = width / max_x;

	if (max_y * scale > height)
		scale = height / max_y;
	return (scale);
}

void Graphical::Core::printCaseInventory(const std::unique_ptr<Case> &block)
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 10;
	Pos margin = _sfml->getMargin();
	float x = _sfml->getWindow().getSize().x - margin.x;
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 1;

	for (int i = 1 ; i <= 7 ; ++i) {
		if (block->getResource(i)) createIcon(i, x, y, margin, padding);
			y += 1;
	}
	if (!block->getEggsId().empty()) createIcon(8, x, y, margin, padding);
		y += 1;
}

void Graphical::Core::printMap(const std::vector<std::unique_ptr<Case>> &map)
{

	float scale = findMapScale(_game->getMapper()->getSize());
	float marginX = (_sfml->getScreen().getSize().x / 2.0f) - (_game->getMapper()->getSize().x / 2.0f * scale);
	float marginY = (_sfml->getScreen().getSize().y / 2.0f) - (_game->getMapper()->getSize().y / 2.0f * scale);

	for (auto &block : map) {
		auto &sprite = _sfml->getBlock(0);
		float size = sprite->getTexture()->getSize().x;
		sprite->setScale({scale / size, scale / size});
		float x = marginX + (block->getPos().x * scale);
		float y = marginY + (block->getPos().y * scale);
		sprite->setPosition(sf::Vector2f(x, y));
		_sfml->getScreen().draw(*sprite);
		if (sprite->getGlobalBounds().contains(_sfml->getMousePosition().x, _sfml->getMousePosition().y))
			printCaseInventory(block);
		if (_filters[2]) {
			for (auto &resource : block->getResources())
				if (resource.second > 0 && resource.first != 7)
					dropStone(resource.first, scale, x, y);
			/*dropStone(1, scale, x, y);
			dropStone(2, scale, x, y);
			dropStone(3, scale, x, y);
			dropStone(4, scale, x, y);
			dropStone(5, scale, x, y);
			dropStone(6, scale, x, y);*/
		}
		if (_filters[7] && block->getResource(7) > 0)
			dropStone(7, scale, x, y);
		if (_filters[8] && block->getResource(8) > 0)
			dropStone(8, scale, x, y);
	}
}
