/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <iostream>
#include <chrono>
#include "Game.hpp"

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
		else if (_type == GAME && event.type == sf::Event::Resized) {
			_sfml->getWindow().setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			_sfml->setScreen({_sfml->getWindow().getSize().x - _sfml->getMargin().x, _sfml->getWindow().getSize().y});
		} else if (_type == GAME && event.type == sf::Event::MouseWheelScrolled)
			_sfml->mouseScrollEvent(event);
		else if (_type == GAME && event.type == sf::Event::MouseButtonPressed)
			_sfml->mouseEvent(event);
	}
	return (0);
}


sf::FloatRect Graphical::Game::createFilter(const int &id, const float &x, const float &y, const Pos &margin, const float &padding)
{
	sf::Color color = (_filters[id] ? sf::Color::Green : sf::Color::Red);
	auto &player = _sfml->getBlock(id);
	player->setScale(static_cast<float>(margin.x) / player->getTexture()->getSize().x,
					 static_cast<float>(margin.x) / player->getTexture()->getSize().y);
	player->setPosition(x, y * padding);
	sf::Color last = player->getColor();
	player->setColor(color);
	_sfml->getWindow().draw(*player);
	player->setColor(last);
	return (player->getGlobalBounds());
}

void Graphical::Game::initFilters()
{
	_filters[11] = true;
	_filters[2] = true;
	_filters[7] = true;
	_filters[8] = true;
	_filters[12] = false;
}

std::map<int, sf::FloatRect> Graphical::Game::printFilters()
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 6;
	float x = _sfml->getWindow().getSize().x - _sfml->getMargin().x;
	Pos margin = _sfml->getMargin();
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

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

long Graphical::Game::eventFilters(const std::map<int, sf::FloatRect> &buttons)
{
	long result = 0;
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return 0;
	for (auto &button : buttons) {
		if (button.second.contains(position)) {
			_filters[button.first] = !_filters[button.first] && true;
			result = 300000000;
		}
	}
	if (_filters[12]) {
		for (auto &filter : _filters)
			filter.second = true;
		_filters[12] = false;
	}
	return result;
}

void Graphical::Game::printGame(std::vector<std::vector<char>> map)
{
	printMap(map);
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

int Graphical::Game::loop()
{
	std::vector<std::vector<char>> map;
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	map.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0});
	_sfml->open(Graphical::Sfml::WINDOW);
	_sfml->createBlocks();
	initFilters();
	while (_sfml->isOpen()) {// && _com->isValidFd(_com->getSocket())) {
		manageEvent();
		//this->manageFd();
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

void Graphical::Game::initCommunication()
{
	if (!_com->sendToFd(_com->getSocket(), "msz"))
		throw std::logic_error("Server is closed.");
};

int main(int ac, char **av)
{
	if (ac != 2 || av[1] == nullptr)
		return (std::cerr << "I need a port argument" << std::endl, 84);
	Graphical::Game game;

	//game.setCommunication(std::make_unique<Graphical::Communication>(std::stoi(av[1])));
	//game.initCommunication();
	game.setDisplayer(std::make_unique<Graphical::Sfml>());
	game.setMap(std::make_unique<Graphical::Map>());
	game.loop();
	return (0);
}

