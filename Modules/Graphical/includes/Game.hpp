/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/
#pragma once

#include <memory>
#include <vector>
#include "Player.hpp"
#include "Sfml.hpp"
#include "Communication.hpp"
#include "Map.hpp"

namespace Graphical {
	class Game {
	public:
		enum GAME_MOD {
			MENU,
			GAME,
			EXIT
		};
		Game() { _type = MENU; };
		~Game() = default;
		inline void addPlayer(std::unique_ptr<Player> player) { _players.emplace_back(std::move(player)); };
		inline void setDisplayer(std::unique_ptr<Sfml> sfml) { _sfml = std::move(sfml); };
		inline void setCommunication(std::unique_ptr<Communication> com) { _com = std::move(com); };
		inline void setMap(std::unique_ptr<Map> map) { _map = std::move(map); };
		inline const std::unique_ptr<Communication> &getCommunication() const { return _com; };
		inline const std::unique_ptr<Sfml> &getDisplayer() const { return _sfml; };
		inline const std::unique_ptr<Map> &getMap() const { return _map; };
		void printGame(std::vector<std::vector<char>> map);
		std::map<GAME_MOD, sf::FloatRect> createButtons();
		void printMenu();
		int loop();
		void initPtrFunction();
		int manageFd();
		int manageEvent();
		int keyManager(sf::Event &event);
		/* FUNCTION PTR_FUNCTION COMMUNICATION */
		int setSize(const std::vector<std::string> &array);
		int setCase(const std::vector<std::string> &array);
		int setTeam(const std::vector<std::string> &array);
		int setPlayer(const std::vector<std::string> &array);
		int setPlayerPosition(const std::vector<std::string> &array);
		int setPlayerLevel(const std::vector<std::string> &array);
		int setPlayerInventory(const std::vector<std::string> &array);
		int setPlayerExpulsion(const std::vector<std::string> &array);
		int setPlayerBroadcast(const std::vector<std::string> &array);
		int setPlayerStartIncantation(const std::vector<std::string> &array);
		int setPlayerEndIncantation(const std::vector<std::string> &array);
		int setPlayerEgg(const std::vector<std::string> &array);
		int setPlayerDropping(const std::vector<std::string> &array);
		int setPlayerCollecting(const std::vector<std::string> &array);
		/* TOOLS */
		void addPlayerToTeam(const std::string &team, const int &playerId)
		{
			if (!isPlayerInTeam(team, playerId))
				_teams[team].push_back(playerId);
		};
		void addATeam(const std::string &team)
		{
			if (!isTeamExist(team))
				_teams[team] = std::vector<int>();

		};
		inline const std::vector<int> &getATeam(const std::string &team) { return _teams[team]; };
		inline const std::map<std::string, std::vector<int>> &getTeams() const { return _teams; };
		inline bool isTeamExist(const std::string &team) { return _teams.find(team) != _teams.end(); };
		const std::unique_ptr<Player> &isPlayerExist(const int &id)
		{
			static std::unique_ptr<Player> notFound = nullptr;

			for (auto &player : _players)
				if (player->getId() == id)
					return player;
			return notFound;
		}
		inline bool isPlayerInTeam(const std::string &team, const int &id) { return std::find(_teams[team].begin(), _teams[team].end(), id) != _teams[team].end(); };
	private:
		std::vector<std::unique_ptr<Player>> _players;
		std::unique_ptr<Sfml> _sfml;
		std::unique_ptr<Communication> _com;
		std::unique_ptr<Map> _map;
		GAME_MOD _type;
		std::map<std::string, std::function<int(const std::vector<std::string> &)>> _ptr_function;
		std::map<std::string, std::vector<int>> _teams; /* team name, player id*/
	};
}