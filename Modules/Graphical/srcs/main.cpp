/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <iostream>
#include <Game.hpp>

int Graphical::Sfml::keyManager(sf::Event &event)
{
	switch (event.key.code) {
		case sf::Keyboard::Tab: {
			if (_type == WINDOW) {
				close();
				open(FULLSCREEN);
			} else if (_type == FULLSCREEN) {
				close();
				open(WINDOW);
			}
			break;
		}
		case sf::Keyboard::Escape : close(); break;
		default: break;
	}
	return (0);
};

int Graphical::Sfml::manageEvent()
{
	sf::Event event{};

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_window.close();
		else if (event.type == sf::Event::KeyPressed)
			keyManager(event);
		else if (event.type == sf::Event::Resized) {
			_window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		}
	}
	return (0);
}

float Graphical::Sfml::findScale(std::vector<std::vector<char>> &map)
{
	size_t max_y = map.size(), max_x = map[0].size();
	float height = _window.getSize().y, width = _window.getSize().x;
	float min_window = height > width ? width : height;
	float max_map = max_y > max_x ? max_y : max_x;
	float scale = min_window / max_map;

	return (scale);
}


void Graphical::Sfml::dropStone(const char &id, const float &scale, const size_t &x, const size_t &y)
{
	float elem = scale / 3.0f;
	auto &sprite_2 = _blocks[id];
	float size_2 = sprite_2->getTexture()->getSize().x;
	sprite_2->setScale({elem / size_2, elem / size_2});
	auto pos = getEntityPos(id);
	sprite_2->setPosition(sf::Vector2f(x + elem * pos.x, y + elem * pos.y));
	_window.draw(*sprite_2);
}

void Graphical::Sfml::print_map(std::vector<std::vector<char>> &map)
{
	size_t x = 0, y = 0;
	float scale = findScale(map);

	for (auto &line : map) {
		x = 0;
		for (auto &block : line) 		{
			if (block == 0) {
				auto &sprite = _blocks[block];
				float size = sprite->getTexture()->getSize().x;
				sprite->setScale({scale / size, scale / size});
				sprite->setPosition(sf::Vector2f(x, y));
				_window.draw(*sprite);

				dropStone(1, scale, x, y);
				dropStone(2, scale, x, y);
				dropStone(3, scale, x, y);
				dropStone(4, scale, x, y);
				dropStone(5, scale, x, y);
				dropStone(6, scale, x, y);
				dropStone(7, scale, x, y);

			}
			x += scale;
		}
		y += scale;
	}
}

int Graphical::Game::loop()
{
	std::vector<std::vector<char>> map;
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	_sfml->open(Graphical::Sfml::WINDOW);
	while (_sfml->isOpen()) {
		_sfml->manageEvent();
		_sfml->clear();
		/**/
		_sfml->print_map(map);
		/**/
		_sfml->display();
	}
	return (0);
}

int main()
{
	Graphical::Game game;

	game.setDisplayer(std::make_unique<Graphical::Sfml>());
	game.setCommunication();
	game.loop();
	return (0);
}

