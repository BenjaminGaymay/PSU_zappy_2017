/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/
#pragma once

#include <memory>
#include <map>
#include <vector>
#include "Tools.hpp"
#include "Execption.hpp"

namespace Graphical {
	class Case {
	public:
		explicit Case(const Pos &pos) : _pos(pos)
		{
			for (std::size_t i = 0 ; i < _size ; ++i) _resources[i] = 0;
		};

		~Case() = default;

		inline void removeResource(int id, std::size_t nb) { if (_resources[id] > 0) _resources[id] -= nb;	};
		inline void addResource(int id, std::size_t nb) { _resources[id] += nb; };
		inline const std::size_t &getResource(int id) { return _resources[id]; };

	private:
		Pos _pos;
		std::map<int, std::size_t> _resources;
		const std::size_t _size = 7;
	};

	class Map {
	public:
		Map(const Pos &size = {0, 0}) : _size(size) {};
		~Map() {};

		void initMap()
		{
			for (int y = 0 ; y < _size.y ; ++y) {
				for (int x = 0 ; x < _size.x; ++x) {
					Pos pos;
					pos.x = x;
					pos.y = y;
					//_map.insert(std::pair<Pos, std::unique_ptr<Case>>(pos, std::make_unique<Case>(pos)));
					_map[pos] = std::make_unique<Case>(pos);
				}
			}
		};

		void setSize(const Pos &size) { _size = size; };
		const Pos &getSize() const { return _size; };
		const std::map<Pos, std::unique_ptr<Case>> &getMap() const { return _map; };
		const std::unique_ptr<Case> &getCase(const Pos &pos) const
		{
			static std::unique_ptr<Case> notFound = nullptr;

			for (auto &elem : _map)
				if (elem.first.x == pos.x && elem.first.y == pos.y)
					return elem.second;
			return notFound;
		};
	private:
		Pos _size;
		std::map<Pos, std::unique_ptr<Case>> _map;

	};
}