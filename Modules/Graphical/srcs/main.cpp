/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <iostream>
#include <Game.hpp>

int Graphical::Game::keyManager(sf::Event &event)
{
	switch (event.key.code) {
		case sf::Keyboard::Tab: {
			if (_sfml->getWindowType() == Graphical::Sfml::WINDOW) {
				_sfml->close();
				_sfml->open(Graphical::Sfml::FULLSCREEN);
			} else if (_sfml->getWindowType() == Graphical::Sfml::FULLSCREEN) {
				_sfml->close();
				_sfml->open(Graphical::Sfml::WINDOW);
			}
			break;
		}
		case sf::Keyboard::Escape : _type = MENU; break;
		default: break;
	}
	return (0);
};

int Graphical::Game::manageEvent()
{
	sf::Event event{};

	while (_sfml->getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_sfml->close();
		else if (event.type == sf::Event::KeyPressed)
			keyManager(event);
		else if (_type == GAME && event.type == sf::Event::Resized)
			_sfml->getWindow().setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		else if (_type == GAME && event.type == sf::Event::MouseWheelScrolled)
			_sfml->mouseScrollEvent(event);
		else if (_type == GAME && event.type == sf::Event::MouseButtonPressed)
			_sfml->mouseEvent(event);
	}
	return (0);
}

float Graphical::Sfml::findMapScale(std::vector<std::vector<char>> &map)
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
	_screen.draw(*sprite_2);
}

void Graphical::Sfml::print_map(std::vector<std::vector<char>> &map)
{
	size_t x = 0, y = 0;
	float scale = findMapScale(map);

	for (auto &line : map) {
		x = 0;
		for (auto &block : line) 		{
			if (block == 0) {
				auto &sprite = _blocks[block];
				float size = sprite->getTexture()->getSize().x;
				sprite->setScale({scale / size, scale / size});
				sprite->setPosition(sf::Vector2f(x, y));
				_screen.draw(*sprite);
				dropStone(1, scale, x, y);
				dropStone(2, scale, x, y);
				dropStone(3, scale, x, y);
				dropStone(4, scale, x, y);
				dropStone(5, scale, x, y);
				dropStone(6, scale, x, y);
				dropStone(7, scale, x, y);
				dropStone(8, scale, x, y);
			}
			x += scale;
		}
		y += scale;
	}
}

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
	_sfml->getScreen().draw(*sprite);
	positions[GAME] = sprite->getGlobalBounds();
	sprite->setPosition(sf::Vector2f((width / 2.0f) - (x / 2.0f), ((height / 2.0f) + y) - (y / 2.0f)));
	_sfml->getScreen().draw(*sprite);
	positions[EXIT] = sprite->getGlobalBounds();

	auto text = _sfml->getText("birdy", "PLAY", 50, sf::Color::White, {0, 0});
	text->setPosition(sf::Vector2f((width / 2.0f) - (50), ((height / 2.0f) - y) - (y / 2)));
	_sfml->getScreen().draw(*text);
	text->setString("QUIT");
	text->setPosition(sf::Vector2f((width / 2.0f) - (50), ((height / 2.0f) + y) - (y / 2)));
	_sfml->getScreen().draw(*text);
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

void Graphical::Game::printGame(std::vector<std::vector<char>> map)
{
	_sfml->print_map(map);
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
	_sfml->createBlocks();
	while (_sfml->isOpen()) {
		manageEvent();
		_sfml->clear();
		switch (_type) {
			case MENU: printMenu(); break;
			case GAME: printGame(map); break;
			case EXIT: _sfml->close();
			default: break;
		}
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

