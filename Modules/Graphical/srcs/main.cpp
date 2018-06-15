/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include "Game.hpp"

void Graphical::Game::clear()
{
	if (_type == GAME) {
		_sfml->getScreen().clear();
	}
	_sfml->getWindow().clear();
}

void Graphical::Game::display()
{
	if (_type == GAME) {
		_sfml->displayScreen();
	}
	_sfml->getWindow().display();
}

int Graphical::Game::initGraphisms()
{
	_sfml->open(Graphical::Sfml::WINDOW);
	_sfml->createBlocks();
	return 0;
}

int Graphical::Game::initMusics()
{
	_music->createMusic("main", "main.ogg");
	return 0;
}

int Graphical::Game::initAll()
{
	initGraphisms();
	initFilters();
	initMusics();
	return 0;
}

int Graphical::Game::loop()
{
	initAll();
	_music->addEvent(Music::MUSIC, Music::PLAY, "main");
	while (_sfml->isOpen() && _com->isValidFd(_com->getSocket())) {
		manageEvent();
		_music->audioManager();
		readServer();
		clear();
		switch (_type) {
			case MENU: printMenu(); break;
			case GAME: printGame(); break;
			case EXIT: _sfml->close();
			default: break;
		}
		display();
	}
	return (0);
}

void Graphical::Game::initCommunication(const std::string &team)
{
	if (!_com->sendToFd(_com->getSocket(), team))
		throw std::logic_error("Server is closed.");
	if (!_com->sendToFd(_com->getSocket(), "msz")) {
		throw std::logic_error("Server is closed.");
	}
};

int main(int ac, char **av)
{
	if (ac != 3 || av[1] == nullptr || av[2] == nullptr)
		return (std::cerr << "I need a port and a team argument" << std::endl, 84);
	Graphical::Game game;

	game.initPtrFunction();
	game.setCommunication(std::make_unique<Graphical::Communication>(std::stoi(av[1])));
	game.setGraphicTeam(av[2]);
	//game.initCommunication(av[2]);
	game.setDisplayer(std::make_unique<Graphical::Sfml>());
	game.setMap(std::make_unique<Graphical::Map>());
	game.setMusic(std::make_unique<Graphical::Music>());
	game.loop();
	return (0);
}

