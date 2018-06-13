/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/

#include <Tools.hpp>
#include "Game.hpp"

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

int Graphical::Game::setSize(const std::vector<std::string> &array)
{
	Pos pos(std::stoi(array[0]), std::stoi(array[1]));

	_map->setSize(pos);
	_map->initMap();
	return 0;
}

int Graphical::Game::setCase(const std::vector<std::string> &array)
{
	Pos pos(std::stoi(array[0]), std::stoi(array[1]));

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
	int id = std::stoi(array[0]);
	Pos pos(std::stoi(array[1]), std::stoi(array[2]));
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
	int id = std::stoi(array[0]);
	Pos pos(std::stoi(array[1]), std::stoi(array[2]));
	int rotation = std::stoi(array[3]);

	const std::unique_ptr<Player> &player = isPlayerExist(id);
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
	const std::unique_ptr<Player> &player = isPlayerExist(id);

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
	const std::unique_ptr<Player> &player = isPlayerExist(id);
	Pos pos(std::stoi(array[1]), std::stoi(array[2]));

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

int Graphical::Game::setPlayerExpulsion(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	const std::unique_ptr<Player> &player = isPlayerExist(id);

	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	return 0;
}

int Graphical::Game::setPlayerBroadcast(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	std::vector<std::string> copy(array.begin() + 1, array.end());
	std::string msg = Graphical::fusion(copy, ' ');
	const std::unique_ptr<Player> &player = isPlayerExist(id);

	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	std::cerr << "Player " << player->getId() << ": send:" << msg << std::endl;
	return 0;
}

int Graphical::Game::setPlayerStartIncantation(const std::vector<std::string> &array)
{
	Pos pos(std::stoi(array[0]), std::stoi(array[1]));
	std::size_t level = std::stoul(array[2]);
	std::vector<int> playersId;

	for (auto elem = array.begin() + 3 ; elem != array.end() ; ++elem) {
		int id = std::stoi(*elem);
		playersId.push_back(id);
	}
	(void) level;
	(void) pos;
	return 0;
}

int Graphical::Game::setPlayerEndIncantation(const std::vector<std::string> &array)
{
	Pos pos(std::stoi(array[0]), std::stoi(array[1]));
	auto result = static_cast<bool>(std::stoi(array[2]));

	(void) pos;
	(void) result;
	return 0;
}

int Graphical::Game::setPlayerDropping(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	int resourceId = std::stoi(array[1]);
	const std::unique_ptr<Player> &player = isPlayerExist(id);

	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	auto &aCase = getMap()->getCase(player->getPosition());
	if (!aCase) {
		std::cerr << "Case not found" << std::endl;
		return 1;
	}
	aCase->addResource(resourceId, 1);
	return 0;
}

int Graphical::Game::setPlayerCollecting(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	int resourceId = std::stoi(array[1]);
	const std::unique_ptr<Player> &player = isPlayerExist(id);

	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	player->addResource(resourceId, 1);
	const std::unique_ptr<Case> &aCase = getMap()->getCase(player->getPosition());
	if (!aCase) {
		std::cerr << "Case not found" << std::endl;
		return 1;
	}
	aCase->removeResource(resourceId, 1);
	return 0;
}

int Graphical::Game::setPlayerLaying(const std::vector<std::string> &array)
{
	(void) array;
	/* player is working so, nothing need to be displayed */
	return 0;
}

int Graphical::Game::setPlayerDeath(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);

	removePlayer(id);
	return (0);
}

int Graphical::Game::setEgg(const std::vector<std::string> &array)
{
	int eggId = std::stoi(array[0]);
	int playerId = std::stoi(array[1]);
	Pos pos(std::stoi(array[2]), std::stoi(array[3]));

	auto &player = isPlayerExist(playerId);
	if (!player) {
		std::cerr << "Player not found" << std::endl;
		return 1;
	}
	const std::unique_ptr<Case> &aCase = getMap()->getCase(pos);
	if (!aCase) {
		std::cerr << "Case not found" << std::endl;
		return 1;
	}
	addEgg(eggId, playerId);
	aCase->addEgg(eggId);
	return 0;
}

int Graphical::Game::setEggHatching(const std::vector<std::string> &array)
{
	int id = std::stoi(array[0]);
	removeEgg(id);
	return 0;
}

int Graphical::Game::setEndGame(const std::vector<std::string> &array)
{
	std::string team = array[0];

	removeATeam(team);
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
	_ptr_function["pex"] = std::bind(&Graphical::Game::setPlayerExpulsion, this, std::placeholders::_1);
	_ptr_function["pbc"] = std::bind(&Graphical::Game::setPlayerBroadcast, this, std::placeholders::_1);
	_ptr_function["pic"] = std::bind(&Graphical::Game::setPlayerStartIncantation, this, std::placeholders::_1);
	_ptr_function["pie"] = std::bind(&Graphical::Game::setPlayerEndIncantation, this, std::placeholders::_1);
	_ptr_function["pfk"] = std::bind(&Graphical::Game::setPlayerLaying, this, std::placeholders::_1);
	_ptr_function["pdr"] = std::bind(&Graphical::Game::setPlayerDropping, this, std::placeholders::_1);
	_ptr_function["pgt"] = std::bind(&Graphical::Game::setPlayerCollecting, this, std::placeholders::_1);
	_ptr_function["pdi"] = std::bind(&Graphical::Game::setPlayerDeath, this, std::placeholders::_1);
	_ptr_function["enw"] = std::bind(&Graphical::Game::setEgg, this, std::placeholders::_1);
	_ptr_function["eht"] = std::bind(&Graphical::Game::setEggHatching, this, std::placeholders::_1);
	_ptr_function["seg"] = std::bind(&Graphical::Game::setEndGame, this, std::placeholders::_1);
}
