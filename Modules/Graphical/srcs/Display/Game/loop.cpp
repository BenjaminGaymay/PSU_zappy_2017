/*
** EPITECH PROJECT, 2018
** student
** File description:
** 15/06/18
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

void Graphical::Core::initFilters()
{
	_filters[13] = false;
	_filters[11] = true;
	_filters[2] = true;
	_filters[7] = true;
	_filters[8] = true;
	_filters[12] = false;
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