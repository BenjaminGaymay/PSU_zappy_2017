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

void Graphical::Core::dropThis(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite = _sfml->getBlock(id);
	float size = sprite->getTexture()->getSize().x;
	sprite->setScale({elem / size, elem / size});
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
}

void Graphical::Core::dropStone(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite = _game->getCristals()->getSprite(id);
	float size =_game->getCristals()->getPadding();

	sprite->setScale({elem / size, elem / size});
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
}

void Graphical::Core::dropEgg(const int &id, const float &scale, const float &x, const float &y)
{
	float elem = scale / 3.0f;
	auto &sprite = _game->getAnimatedEggs()->getSprite(id);
	float size = _game->getAnimatedEggs()->getPadding();

	sprite->setScale({elem / size, elem / size});
	auto pos = getEntityPos(id);
	sprite->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_sfml->getScreen().draw(*sprite);
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

	for (int i = 1 ; i < 7 ; ++i) {
		if (block->getResource(i) > 0) createIcon(filterNb, 22, x, y, margin, padding, _game->getCristals()->getColor(i));
			y += 1;
	}
	if (block->getResource(7) > 0) createIcon(filterNb, 7, x, y, margin, padding);
		y += 1;
	if (!block->getEggsId().empty()) createIcon(filterNb, 8, x, y, margin, padding);
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
		if (!_move && sprite->getGlobalBounds().contains(_sfml->getMousePosition().x, _sfml->getMousePosition().y))
			printCaseInventory(block);
		if (_filters[2]) {
			for (auto &resource : block->getResources()) {
				if(resource.first >= 7)
					break;
				if (resource.second > 0)
					dropStone(resource.first, scale, x, y);
			}
			/*dropStone(1, scale, x, y);
			dropStone(2, scale, x, y);
			dropStone(3, scale, x, y);
			dropStone(4, scale, x, y);
			dropStone(5, scale, x, y);
			dropStone(6, scale, x, y);*/
		}
		if (_filters[7] && block->getResource(7) > 0)
			dropThis(7, scale, x, y);
		if (_filters[8] && !block->getEggsId().empty())
			dropEgg(8, scale, x, y);
	}
}
