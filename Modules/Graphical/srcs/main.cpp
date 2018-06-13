/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <iostream>
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
			_sfml->setScreen(_sfml->getWindow().getSize());
		} else if (_type == GAME && event.type == sf::Event::MouseWheelScrolled)
			_sfml->mouseScrollEvent(event);
		else if (_type == GAME && event.type == sf::Event::MouseButtonPressed)
			_sfml->mouseEvent(event);
	}
	return (0);
}

void Graphical::Game::printGame(std::vector<std::vector<char>> map)
{
	_sfml->print_map(map);
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

