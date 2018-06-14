/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/
#pragma once

#include <SFML/Graphics/Font.hpp>
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
			addFont("birdy", _fontPath + "birdy.ttf");
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
				_screen.create(_window.getSize().x - _margin.x, _window.getSize().y);
			}
			_windowType = type;
		};

		void close()
		{
			if (_window.isOpen())
				_window.close();
		};
		sf::RenderWindow &getWindow() { return _window; };
		sf::RenderTexture &getScreen() { return _screen; };
		void setScreen(const sf::Vector2u &size)
		{
			_screen.clear();
			_screen.create(size.x, size.y);
		}
		bool isOpen() { return _window.isOpen(); };
		void clear()
		{
			_window.clear();
			_screen.clear();
		};
		void display()
		{
			_window.draw(sf::Sprite(_screen.getTexture()));
			_window.display();
			_screen.display();
		};
		void createBlocks();
		bool createTexture(const int &index, const std::string &path,
						   std::map<const int, std::unique_ptr<sf::Texture>> &textures);
		bool createSprite(const int &index, const std::string &path,
						  std::map<const int, std::unique_ptr<sf::Sprite>> &sprites,
						  std::map<const int, std::unique_ptr<sf::Texture>> &textures);
		std::unique_ptr<sf::Font> &getFont(const std::string &name);
		void addFont(const std::string &key, const std::string &maccro);
		void addFont(const std::string &key, std::unique_ptr<sf::Font> &font);
		std::unique_ptr<sf::Sprite> &getBlock(const int &id) { return _blocks[id]; };
		void text(const std::string &font_name, const std::string &line, const std::size_t &size, const sf::Color &textColor,  const sf::Vector2f &position);
		std::unique_ptr<sf::Text> getText(const std::string &font_name, const std::string &line, const std::size_t &size, const sf::Color &textColor, const sf::Vector2f &position);
		const mod &getWindowType() const { return _windowType; };
		void mouseScrollEvent(sf::Event &event);
		void mouseEvent(sf::Event &event);
		void resetView();
		const Pos &getMargin() const { return _margin; };
	private:
		std::map<const int, std::unique_ptr<sf::Sprite>> _blocks;
		std::map<const int, std::unique_ptr<sf::Texture>> _textures;
		std::map<const std::string, std::unique_ptr<sf::Font>> _fonts;
		std::map<const int, std::unique_ptr<sf::Sprite>> _buttons;
		sf::RenderWindow _window;
		sf::RenderTexture _screen;
		float _zoom = 1;
		const Pos _margin = {50, 0};
		mod _windowType;
		const std::string _picturePath = "assets/pictures/";
		const std::string _fontPath = "assets/fonts/";
	};
}