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
		void addPlayer(std::unique_ptr<Player> player) { _players.emplace_back(std::move(player)); };
		void setDisplayer(std::unique_ptr<Sfml> sfml) { _sfml = std::move(sfml); };
		void setCommunication() {};
		//const std::unique_ptr<> &getCommunication() const { return _com; };
		const std::unique_ptr<Sfml> &getDisplayer() const { return _sfml; };
		void printGame(std::vector<std::vector<char>> map);
		std::map<GAME_MOD, sf::FloatRect> createButtons();
		void printMenu();
		int loop();
		int manageEvent();
		int keyManager(sf::Event &event);
	private:
		std::vector<std::unique_ptr<Player>> _players;
		std::unique_ptr<Sfml> _sfml;
		//std::unique_ptr<> _com;
		GAME_MOD _type;
	};
}