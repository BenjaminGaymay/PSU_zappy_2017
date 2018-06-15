/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/

#include <chrono>
#include "Core.hpp"

void Graphical::Core::createIcon(const int &id, const float &x, const float &y, const Pos &margin, const float &padding)
{
	auto &player = _sfml->getBlock(id);
	player->setScale(static_cast<float>(margin.x) / player->getTexture()->getSize().x,
					 static_cast<float>(margin.x) / player->getTexture()->getSize().y);
	player->setPosition(x, y * padding);
	_sfml->getWindow().draw(*player);
}

sf::FloatRect Graphical::Core::createFilter(const int &id, const float &x, const float &y, const Pos &margin, const float &padding)
{
	sf::Color color = (_filters[id] ? sf::Color::Green : sf::Color::Red);
	auto &player = _sfml->getBlock(id);
	player->setScale(static_cast<float>(margin.x) / player->getTexture()->getSize().x,
					 static_cast<float>(margin.x) / player->getTexture()->getSize().y);
	player->setPosition(x, y * padding);
	sf::Color last = player->getColor();
	player->setColor(color);
	createIcon(15, x, y, margin, padding);
	_sfml->getWindow().draw(*player);
	player->setColor(last);
	return (player->getGlobalBounds());
}

void Graphical::Core::initFilters()
{
	_filters[13] = false;
	_filters[11] = true;
	_filters[2] = true;
	_filters[7] = true;
	_filters[8] = true;
	_filters[12] = false;
}

std::map<int, sf::FloatRect> Graphical::Core::printFilters()
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 6;
	Pos margin = _sfml->getMargin();
	margin.x /= 2;
	float x = _sfml->getWindow().getSize().x - margin.x;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

	buttons[13] = createFilter(13, x, y, margin, padding);
	y += 1;
	buttons[11] = createFilter(11, x, y, margin, padding);
	y += 1;
	buttons[2] = createFilter(2, x, y, margin, padding);
	y += 1;
	buttons[7] = createFilter(7, x, y, margin, padding);
	y += 1;
	buttons[8] = createFilter(8, x, y, margin, padding);
	y += 1;
	buttons[12] = createFilter(12, x, y, margin, padding);
	return buttons;
}

long Graphical::Core::eventFilters(const std::map<int, sf::FloatRect> &buttons)
{
	long result = 0;
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return 0;
	for (auto &button : buttons) {
		if (button.second.contains(position)) {
			_filters[button.first] = !_filters[button.first] && true;
			result = 300000000; // antispam
		}
	}
	if (_filters[13]) {
		_type = MENU;
		_filters[13] = false;
	}
	if (_filters[12]) {
		for (auto &filter : _filters)
			if (filter.first != 13)
				filter.second = true;
		_filters[12] = false;
	}
	return result;
}

void Graphical::Core::printInventoryCases()
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 10;
	Pos margin = _sfml->getMargin();
	float x = _sfml->getWindow().getSize().x - margin.x;
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

	createIcon(15, x, y, margin, padding);
	createIcon(14, x, y, margin, padding);
	y +=1;
	while (y < 10) {
		createIcon(15, x, y, margin, padding);
		y += 1;
	}
}

void Graphical::Core::printToolbar()
{
	auto &player = _sfml->getBlock(16);
	player->setScale(_sfml->getMargin().x, _sfml->getWindow().getSize().y);
	player->setPosition(_sfml->getWindow().getSize().x - _sfml->getMargin().x, 0);
	_sfml->getWindow().draw(*player);
}

void Graphical::Core::printGame()
{
	printToolbar();
	printInventoryCases();
	printMap(_game->getMapper()->getMap());
	auto buttons = printFilters();
	static long last = 0;


	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	long now = time.time_since_epoch().count() ;

	if (now > last) {
		auto antiSpam = eventFilters(buttons);
		if (antiSpam > 0)
			last = now + antiSpam;
	}
}