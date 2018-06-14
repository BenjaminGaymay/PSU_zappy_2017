/*
** EPITECH PROJECT, 2018
** student
** File description:
** 12/06/18
*/
#pragma once

#include <random>
#include <memory>
#include <map>
#include <vector>
#include <SFML/Graphics/Rect.h>
#include "Tools.hpp"
#include "Execption.hpp"
#include "Egg.hpp"

namespace Graphical {
	class Case {
	public:
		explicit Case(const Pos &pos) : _pos(pos)
		{
			for (std::size_t i = 1 ; i <= _size ; ++i) _resources[i] = 0;
		};

		~Case() = default;

		inline void removeResource(int id, std::size_t nb) { if (_resources[id] > 0) _resources[id] -= nb;	};
		inline void addResource(int id, std::size_t nb) { _resources[id] += nb; };
		inline const std::size_t &getResource(int id) { return _resources[id]; };
		inline const std::map<int, std::size_t> &getResources() { return _resources; };
		inline void addEgg(int id) { _eggsId.push_back(id); };
		const std::vector<int> getEggsId() const { return _eggsId; };
		const Pos &getPos() const { return _pos; };
	private:
		Pos _pos;
		std::map<int, std::size_t> _resources;
		const std::size_t _size = 7;
		std::vector<int> _eggsId; /* contain id of egg */
	};

	class Map {
	public:
		Map(const Pos &size = {0, 0}) : _size(size) {};
		~Map() {};

		void initMap()
		{
			static std::default_random_engine generator;
			std::uniform_int_distribution<int> random(1, 6);

			for (int y = 0 ; y < _size.y ; ++y) {
				for (int x = 0 ; x < _size.x; ++x) {
					Pos pos(x, y);
					std::unique_ptr<Case> aCase = std::make_unique<Case>(pos);
					//aCase->addResource(random(generator), 1);
					aCase->addResource(1, 1);
					aCase->addResource(2, 1);
					aCase->addResource(3, 1);
					aCase->addResource(4, 1);
					aCase->addResource(5, 1);
					aCase->addResource(6, 1);
					aCase->addResource(7, 1);
					_map.emplace_back(std::move(aCase));
				}
			}
		};

		void setSize(const Pos &size) { _size = size; };
		const Pos &getSize() const { return _size; };
		const std::vector<std::unique_ptr<Case>> &getMap() const { return _map; };
		const std::unique_ptr<Case> &getCase(const Pos &pos) const
		{
			static std::unique_ptr<Case> notFound = nullptr;

			for (auto &elem : _map)
				if (elem->getPos().x == pos.x && elem->getPos().y == pos.y)
					return elem;
			return notFound;
		};
	private:
		Pos _size;
		std::vector<std::unique_ptr<Case>> _map;

	};
}