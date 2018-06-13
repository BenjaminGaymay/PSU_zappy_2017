/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include <Tools.hpp>
#include "Game.hpp"

int Graphical::Game::setSize(const std::vector<std::string> &array)
{
	Pos pos;

	pos.x = std::stoi(array[0]);
	pos.y = std::stoi(array[1]);
	_map->setSize(pos);
	_map->initMap();
	return 0;
}

int Graphical::Game::setCase(const std::vector<std::string> &array)
{
	Pos pos;

	pos.x = std::stoi(array[0]);
	pos.y = std::stoi(array[1]);
	auto &aCase = _map->getCase(pos);
	if (!aCase)
		return 1;
	int index = 0;
	for (auto elem = array.begin() + 2 ; elem < array.end() ; ++elem) {
		auto str = *elem;
		aCase->addResource(index, std::stoul(str));
		++index;
	}
	return 0;
}

int Graphical::Game::setTeam(const std::vector<std::string> &array)
{
	const std::string team = array[0];

	addATeam(team);
	return 0;
}

int Graphical::Game::setPlayer(const std::vector<std::string> &array)
{
	Pos pos;

	int id = std::stoi(array[0]);
	pos.x = std::stoi(array[1]);
	pos.y = std::stoi(array[2]);
	int rotation = std::stoi(array[3]);
	std::size_t level = std::stoul(array[4]);
	const std::string team = array[5];
	if (!isTeamExist(team) || isPlayerExist(id)) {
		std::cerr << "Player or team not found" << std::endl;
		return 1;
	}
	addPlayer(std::make_unique<Player>(id, pos, rotation, level, team));
	return 0;
}

int Graphical::Game::setPlayerPosition(const std::vector<std::string> &array)
{
	Pos pos;

	int id = std::stoi(array[0]);
	pos.x = std::stoi(array[1]);
	pos.y = std::stoi(array[2]);
	int rotation = std::stoi(array[3]);

	std::unique_ptr<Player> &player = isPlayerExist(id);
	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	player->setPosition(pos);
	player->setRotation(rotation);
	return 0;
}

int Graphical::Game::setPlayerLevel(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	std::size_t level = std::stoul(array[1]);
	std::unique_ptr<Player> &player = isPlayerExist(id);

	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	player->setLevel(level);
	return 0;
}

int Graphical::Game::setPlayerInventory(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	std::unique_ptr<Player> &player = isPlayerExist(id);
	Pos pos;

	pos.x = std::stoi(array[1]);
	pos.y = std::stoi(array[2]);
	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	player->setPosition(pos);
	int index = 0;
	for (auto elem = array.begin() + 3 ; elem < array.end() ; ++elem) {
		auto str = *elem;
		player->addResource(index, std::stoul(str));
		++index;
	}
	return 0;
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
	return 0;
}

void Graphical::Game::initPtrFunction()
{
	_ptr_function["msz"] = std::bind(&Graphical::Game::setSize, this, std::placeholders::_1);
	_ptr_function["bct"] = std::bind(&Graphical::Game::setCase, this, std::placeholders::_1);
	_ptr_function["tna"] = std::bind(&Graphical::Game::setTeam, this, std::placeholders::_1);
	_ptr_function["pnw"] = std::bind(&Graphical::Game::setPlayer, this, std::placeholders::_1);
	_ptr_function["ppo"] = std::bind(&Graphical::Game::setPlayerPosition, this, std::placeholders::_1);
	_ptr_function["plv"] = std::bind(&Graphical::Game::setPlayerLevel, this, std::placeholders::_1);
	_ptr_function["pin"] = std::bind(&Graphical::Game::setPlayerInventory, this, std::placeholders::_1);
}
