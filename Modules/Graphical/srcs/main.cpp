/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include "Core.hpp"

void Graphical::Core::clear()
{
	if (_type == GAME) {
		_sfml->getScreen().clear();
	}
	_sfml->getWindow().clear();
}

void Graphical::Core::display()
{
	if (_type == GAME) {
		_sfml->displayScreen();
	}
	_sfml->getWindow().display();
}

int Graphical::Core::initGraphisms()
{
	_sfml->open(Graphical::Sfml::WINDOW);
	_sfml->createBlocks();
	return 0;
}

int Graphical::Core::initMusics()
{
	_music->createMusic("main", "main.ogg");
	return 0;
}

int Graphical::Core::initAll()
{
	initGraphisms();
	initFilters();
	initMusics();
	return 0;
}

int Graphical::Core::loop()
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

int main(int ac, char **av)
{
	if (ac != 3 || av[1] == nullptr || av[2] == nullptr)
		return (std::cerr << "I need a port and a team argument" << std::endl, 84);
	Graphical::Core core;

	core.initPtrFunction();
	core.setCommunication(std::make_unique<Graphical::Communication>(std::stoi(av[1])));
	core.setGraphicTeam(av[2]);
	core.setDisplayer(std::make_unique<Graphical::Sfml>());
	core.setMusic(std::make_unique<Graphical::Music>());
	core.setGame(std::make_unique<Graphical::Game>());
	core.getGame()->setMapper(std::make_unique<Graphical::Map>());
	core.loop();
	return (0);
}

