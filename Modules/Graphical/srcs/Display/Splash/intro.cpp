/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
*/

#include <chrono>
#include "Core.hpp"

std::unique_ptr<sf::Sprite> &Graphical::Core::createSplashIntro()
{
	auto width = _sfml->getWindow().getSize().x;
	auto height = _sfml->getWindow().getSize().y;
	auto &sprite = _sfml->getBlock(17);
	float x = (width / 2.0f) -
			  ((sprite->getTexture()->getSize().x * sprite->getScale().x) /
			   2.0f);
	float y = (height / 2.0f) -
			  ((sprite->getTexture()->getSize().y * sprite->getScale().y) /
			   2.0f);
	sprite->setPosition(x, y);
	return sprite;
}

void Graphical::Core::printSplashIntro()
{
	static sf::Uint8 alpha = 0;
	static bool visible = true;
	static long last = std::chrono::system_clock::now().time_since_epoch().count();
	auto &sprite = createSplashIntro();
	sf::Uint8 padding = 5;

	long now = std::chrono::system_clock::now().time_since_epoch().count();
	if (visible) {
		if (now <= last + 800000000) {
			std::cerr << "- " << (int)alpha << std::endl;
			alpha += alpha < (255 - padding) ? padding : 0;
		} else {
			std::cerr << "inversion" << std::endl;
			visible = false;
			last = std::chrono::system_clock::now().time_since_epoch().count();
		}
	} else {
		if (now <= last + 800000000) {
			std::cerr << "+ " << (int)alpha << std::endl;
			alpha -= alpha > padding ? padding : 0;
		} else
			_type = MENU;
	}
	sprite->setColor({200, 100, 100, alpha});
	_sfml->getWindow().draw(*sprite);
}