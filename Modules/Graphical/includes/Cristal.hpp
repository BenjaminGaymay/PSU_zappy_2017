/*
** EPITECH PROJECT, 2018
** student
** File description:
** 16/06/18
*/
#pragma once

#include <memory>
#include <chrono>
#include "Sfml.hpp"

namespace Graphical {
	class Cristal {
	public:
		Cristal(std::shared_ptr<Graphical::Sfml> &sfml, const int &id) : _id(id), _x(0), _y(0)
		{
			_sfml = sfml;
		};

		~Cristal() = default;

		void setX(std::unique_ptr<sf::Sprite> &sprite) {
			static long last = std::chrono::system_clock::now().time_since_epoch().count();
			long now = std::chrono::system_clock::now().time_since_epoch().count();

			if (now > last + 100000000) {
				last = std::chrono::system_clock::now().time_since_epoch().count();
				_x += 64;
				if (_x >= sprite->getTexture()->getSize().x)
					_x = 0;
			}
		}

		std::unique_ptr<sf::Sprite> &getCristalSprite(const int &id)
		{
			auto &sprite = _sfml->getBlock(_id);

			setX(sprite);
			sprite->setTextureRect({static_cast<int>(_x), static_cast<int>(_y), 64, 64});

			switch (id) {
				case 1: sprite->setColor(sf::Color::Blue); break;
				case 2: sprite->setColor(sf::Color::Red); break; //RED
				case 3: sprite->setColor(sf::Color::Yellow); break;
				case 4: sprite->setColor(sf::Color::Cyan); break;
				case 5: sprite->setColor(sf::Color::Green); break;
				case 6: sprite->setColor(sf::Color::Magenta); break;
				default: break;
			}
			return sprite;
		}
	private:
		std::shared_ptr<Graphical::Sfml> _sfml;
		int _id;
		std::size_t _x;
		std::size_t _y;
	};
}