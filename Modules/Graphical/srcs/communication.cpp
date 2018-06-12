/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include "Game.hpp"

int Graphical::Game::setSize(const std::vector<std::string> &array)
{
	Pos pos;
	pos.x = std::stoi(array[0]);
	pos.y = std::stoi(array[1]);
	_map->setSize(pos);
	_map->initMap();
}

int Graphical::Game::setCase(const std::vector<std::string> &array)
{
	Pos pos;
	pos.x = std::stoi(array[0]);
	pos.y = std::stoi(array[1]);
	auto &aCase = _map->getCase(pos);
	int index = 0;
	for (auto elem = array.begin() + 2 ; elem < array.end() ; ++elem) {
		auto str = *elem;
		aCase->addResource(index, std::stoul(str));
		++index;
	}
}

void Graphical::Game::initPtrFunction()
{
	_ptr_function["msz"] = std::bind(&Graphical::Game::setSize, this, std::placeholders::_1);
	_ptr_function["bct"] = std::bind(&Graphical::Game::setCase, this, std::placeholders::_1);
}

int Graphical::Game::manageFd()
{
	auto array = _com->readFd(_com->getSocket());
	for (auto &line : array) {
		auto command = Graphical::explode(line, ' ');
		auto aFunction = _ptr_function[command[0]];
		if (aFunction) {
			command.erase(command.begin());
			aFunction(command);
		}
	}
}