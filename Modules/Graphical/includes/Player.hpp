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
		Player(const Graphical::Pos &pos, const int &rota, const int &id)
				: _pos(pos), _rotation(rota), _id(id)
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
		const Pos &getPosition() const { return _pos; };
		const int &getRotation() const { return _rotation; };
		const int &getId() const { return _id; };
	private:
		Pos _pos;
		int _rotation;
		int _id;
	};
}