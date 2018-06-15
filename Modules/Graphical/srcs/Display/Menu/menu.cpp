/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Core.hpp"

sf::FloatRect Graphical::Core::createButton(std::unique_ptr<sf::Sprite> &sprite, const sf::Vector2f &position)
{
	sprite->setPosition(position);
	_sfml->getWindow().draw(*sprite);

	return sprite->getGlobalBounds();
}

std::map<Graphical::Core::GAME_MOD, sf::FloatRect> Graphical::Core::createButtons()
{
	std::map<GAME_MOD, sf::FloatRect> positions;
	float width = _sfml->getWindow().getSize().x;
	float height = _sfml->getWindow().getSize().y;
	auto &sprite = _sfml->getBlock(10);
	float scale = 0.5f, x = 0, y = 0;

	sprite->setScale({scale, scale});
	x = sprite->getTexture()->getSize().x * scale;
	y = sprite->getTexture()->getSize().y * scale;

	positions[GAME] = createButton(sprite, sf::Vector2f((width / 2.0f) - (x / 2.0f), ((height / 2.0f) - y) - (y / 2.0f)));
	positions[EXIT] = createButton(sprite, sf::Vector2f((width / 2.0f) - (x / 2.0f), ((height / 2.0f) + y) - (y / 2.0f)));

	_sfml->text("birdy", "PLAY", 50, sf::Color::White, sf::Vector2f((width / 2.0f) - (50), ((height / 2.0f) - y) - (y / 2)));
	_sfml->text("birdy", "EXIT", 50, sf::Color::White, sf::Vector2f((width / 2.0f) - (50), ((height / 2.0f) + y) - (y / 2)));
	return positions;
}

void Graphical::Core::printMenu()
{
	std::map<GAME_MOD, sf::FloatRect> buttons = createButtons();
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) return ;
	for (auto &button : buttons)
		if (button.second.contains(position))
			_type = button.first;
}