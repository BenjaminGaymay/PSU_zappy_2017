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
		explicit Player(const Graphical::Pos &pos): _pos(pos), _rotation(0) {};
		~Player() = default;
		void setPosition(const Graphical::Pos &pos)
		{
			if (_pos.x == pos.x && _pos.y != pos.y)
				_rotation = _pos.y > _pos.y ? 180 : 0;
			else if (_pos.y == pos.y && _pos.x != pos.x)
				_rotation = _pos.x > _pos.x ? 90 : 270;
			_pos = pos;
		};
		const int &getRotation() const { return _rotation; };
		const Pos &getPosition() const { return _pos; };
	private:
		Pos _pos;
		int _rotation;
	};
}