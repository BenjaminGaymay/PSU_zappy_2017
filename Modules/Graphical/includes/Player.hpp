/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#pragma once
#include "Tools.hpp"

namespace Graphical {
	class Player {
	public:
		Player(const int &id, const Graphical::Pos &pos, const int &rota, const std::size_t &level, const std::string &team)
				: _id(id), _pos(pos), _rotation(rota), _level(level), _team(team)
		{
		};

		~Player() = default;

		void setPosition(const Graphical::Pos &pos)
		{
			if (_pos.x == pos.x && _pos.y != pos.y)
				_rotation = pos.y > _pos.y ? 180 : 0;
			else if (_pos.y == pos.y && _pos.x != pos.x)
				_rotation = pos.x > _pos.x ? 90 : 270;
			_pos = pos;
		};
		void setRotation(const int &rotation) { _rotation = rotation; };
		void setLevel(const std::size_t &level) { _level = level; };
		const int &getId() const { return _id; };
		const Pos &getPosition() const { return _pos; };
		const int &getRotation() const { return _rotation; };
		const std::size_t &getLevel() const { return _level; };
		const std::string &getTeam() const { return _team; };
	private:
		const int _id;
		Pos _pos;
		int _rotation;
		std::size_t _level;
		const std::string _team;
	};
}