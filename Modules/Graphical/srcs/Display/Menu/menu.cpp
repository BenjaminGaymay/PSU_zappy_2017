/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Game.hpp"

std::map<Graphical::Game::GAME_MOD, sf::FloatRect> Graphical::Game::createButtons()
{
	std::map<GAME_MOD, sf::FloatRect> positions;
	float width = _sfml->getWindow().getSize().x;
	float height = _sfml->getWindow().getSize().y;
	auto &sprite = _sfml->getBlock(10);
	float scale = 0.5f, x = 0, y = 0;

	sprite->setScale({scale, scale});
	x = sprite->getTexture()->getSize().x * scale;
	y = sprite->getTexture()->getSize().y * scale;

	sprite->setPosition(sf::Vector2f((width / 2.0f) - (x / 2.0f), ((height / 2.0f) - y) - (y / 2.0f)));
	_sfml->getWindow().draw(*sprite);
	positions[GAME] = sprite->getGlobalBounds();
	sprite->setPosition(sf::Vector2f((width / 2.0f) - (x / 2.0f), ((height / 2.0f) + y) - (y / 2.0f)));
	_sfml->getWindow().draw(*sprite);
	positions[EXIT] = sprite->getGlobalBounds();

	auto text = _sfml->getText("birdy", "PLAY", 50, sf::Color::White, {0, 0});
	text->setPosition(sf::Vector2f((width / 2.0f) - (50), ((height / 2.0f) - y) - (y / 2)));
	_sfml->getWindow().draw(*text);
	text->setString("QUIT");
	text->setPosition(sf::Vector2f((width / 2.0f) - (50), ((height / 2.0f) + y) - (y / 2)));
	_sfml->getWindow().draw(*text);
	return positions;
}

void Graphical::Game::printMenu()
{
	std::map<GAME_MOD, sf::FloatRect> buttons = createButtons();
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return ;
	for (auto &button : buttons) {
		if (button.second.contains(position))
			_type = button.first;
	}
}