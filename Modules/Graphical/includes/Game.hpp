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
		Game() {};
		~Game() = default;
		void setDisplayer(std::unique_ptr<Sfml> sfml) { _sfml = std::move(sfml); };
		void setCommunication() {};
		//const std::unique_ptr<> &getCommunication() const { return _com; };
		const std::unique_ptr<Sfml> &getDisplayer() const { return _sfml; };
		int loop();
	private:
		std::vector<Player> _players;
		std::unique_ptr<Sfml> _sfml;
		//std::unique_ptr<> _com;
	};
}