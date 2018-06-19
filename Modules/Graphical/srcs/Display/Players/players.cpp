/*
** EPITECH PROJECT, 2018
** student
** File description:
** 18/06/18
*/

#include "Core.hpp"

void Graphical::Core::printPlayerInfo(std::unique_ptr<Player> &player, const int &padding, const Pos<float> &pos)
{
	int y = 0;
	auto size = static_cast<std::size_t>(padding / 4);

	_sfml->text("birdy", "Id:" + std::to_string(player->getId()), size, sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
	y += 1;
	_sfml->text("birdy", "Team:" + player->getTeam(), size, sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
	y += 1;
	_sfml->text("birdy", "Level:" + std::to_string(player->getLevel()), size, sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
	y += 1;
	_sfml->text("birdy", "Inventory:", size,  sf::Color::White, {pos.x, (y * size) + (pos.y * padding)});
}

void Graphical::Core::printPlayers()
{
	auto &aCase = _game->getMapper()->getCase(_caseSelected);
	if (!aCase)
		return ;
	auto &players = aCase->getPlayersId();

	const std::size_t filterNb = players.size() < 10 ? 10 : players.size();
	Pos<int> margin = {static_cast<int>(_sfml->getWindow().getSize().x), 0};
	int padding = static_cast<int>(_sfml->getWindow().getSize().y / filterNb);
	float x = 0;
	float y = 0;

	for (auto &aPlayer : players) {
		auto &player = _game->getPlayer(aPlayer);
		if (player) {
			auto &icon = createIcon(filterNb, 15, x, y, margin, padding);
			createIcon(filterNb, 24, x, y, margin, padding, _game->getColor(player->getTeam()));
			printPlayerInfo(player, padding, {icon->getScale().x * icon->getTexture()->getSize().x, y});
			++y;
		}
	}
}