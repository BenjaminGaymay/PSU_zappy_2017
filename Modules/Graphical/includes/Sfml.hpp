/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/
#pragma once

#include <SFML/Graphics.hpp>
#include "Tools.hpp"

namespace Graphical {
	class Sfml {
	public:
		enum mod {
			FULLSCREEN,
			WINDOW,
		};
		Sfml()
		{
			createBlocks();
		};

		~Sfml()
		{
			close();
		};

		void open(mod type)
		{
			if (!_window.isOpen()) {
				if (type == FULLSCREEN)
					_window.create(sf::VideoMode(1080, 720), "ZAPPY", sf::Style::Fullscreen);
				else if (type == WINDOW)
					_window.create(sf::VideoMode(1080, 720), "ZAPPY", sf::Style::Close | sf::Style::Resize);
				_window.setFramerateLimit(30);
			}
			_type = type;
		};

		void close()
		{
			if (_window.isOpen())
				_window.close();
		};
		sf::RenderWindow &getWindow() { return _window; };
		bool isOpen() { return _window.isOpen(); };
		int manageEvent();
		void clear() { _window.clear(); };
		void display() { _window.display(); };
		int keyManager(sf::Event &event);
		void print_map(std::vector<std::vector<char>> &map);
		void createBlocks();
		bool createTexture(const int &index, const std::string &path,
						   std::map<const int, std::unique_ptr<sf::Texture>> &textures);
		bool createSprite(const int &index, const std::string &path,
						  std::map<const int, std::unique_ptr<sf::Sprite>> &sprites,
						  std::map<const int, std::unique_ptr<sf::Texture>> &textures);
		float findScale(std::vector<std::vector<char>> &map);
		Pos getEntityPos(const char &block);
		void dropStone(const char &id, const float &scale, const size_t &x, const size_t &y);
	private:
		std::map<const int, std::unique_ptr<sf::Sprite>> _blocks;
		std::map<const int, std::unique_ptr<sf::Texture>> _textures;
		sf::RenderWindow _window;
		mod _type;
		const std::string _picturePath = "assets/picture/";
	};
}