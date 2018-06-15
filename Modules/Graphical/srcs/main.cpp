/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include "Core.hpp"

int main(int ac, char **av)
{
	if (ac != 3 || av[1] == nullptr || av[2] == nullptr)
		return (std::cerr << "I need a port and a team argument" << std::endl, 84);
	Graphical::Core core;

	core.initPtrFunction();
	core.setCommunication(std::make_unique<Graphical::Communication>(std::stoi(av[1])));
	core.setGraphicTeam(av[2]);
	core.setDisplayer(std::make_unique<Graphical::Sfml>());
	core.setMusic(std::make_unique<Graphical::Music>());
	core.setGame(std::make_unique<Graphical::Game>());
	core.getGame()->setMapper(std::make_unique<Graphical::Map>());
	core.loop();
	return (0);
}

