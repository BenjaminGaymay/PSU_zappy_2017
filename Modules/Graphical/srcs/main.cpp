/*
** EPITECH PROJECT, 2018
** student
** File description:
** 11/06/18
*/

#include <iostream>
#include <chrono>
#include "Game.hpp"

int Graphical::Game::keyManager(sf::Event &event)
{
	switch (event.key.code) {
		case sf::Keyboard::Tab: {
			if (_sfml->getWindowType() == Graphical::Sfml::WINDOW) {
				_sfml->close();
				_sfml->open(Graphical::Sfml::FULLSCREEN);
			} else if (_sfml->getWindowType() == Graphical::Sfml::FULLSCREEN) {
				_sfml->close();
				_sfml->open(Graphical::Sfml::WINDOW);
			}
			break;
		}
		case sf::Keyboard::Escape : _type = MENU; break;
		case sf::Keyboard::Space : _move = !_move; break;
		default: break;
	}
	return (0);
};

void Graphical::Game::mouseEvent(const sf::Event &event, const bool &move)
{
	(void) event;
	sf::View view = _sfml->getScreen().getView();
	sf::Vector2i mousePos = sf::Mouse::getPosition(_sfml->getWindow());
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (!(mousePos.x > 0 &&
			  mousePos.y > 0 &&
			  mousePos.x < static_cast<int>(_sfml->getWindow().getSize().x - _sfml->getMargin().x) &&
			  mousePos.y < static_cast<int>(_sfml->getWindow().getSize().y)))
			return;
		sf::Vector2f mouseScreenPos = _sfml->getScreen().mapPixelToCoords(mousePos, _sfml->getScreen().getView());
		_sfml->setMousePosition({static_cast<int>(mouseScreenPos.x), static_cast<int>(mouseScreenPos.y)});
		mousePos.x = static_cast<int>(
				(mousePos.x / static_cast<float>(_sfml->getScreen().getSize().x)) *
				(view.getSize().x));
		mousePos.y = static_cast<int>(
				(mousePos.y / static_cast<float>(_sfml->getScreen().getSize().y)) *
				(view.getSize().y));
		mousePos.x = static_cast<int>(mousePos.x - (view.getSize().x / 2));
		mousePos.y = static_cast<int>(mousePos.y - (view.getSize().y / 2));
		if (move)
			view.move(mousePos.x, mousePos.y);
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		view.setCenter((_sfml->getWindow().getSize().x - _sfml->getMargin().x) / 2.0f, _sfml->getWindow().getSize().y / 2.0f);
	}
	_sfml->getScreen().setView(view);
}

int Graphical::Game::manageEvent()
{
	sf::Event event{};

	while (_sfml->getWindow().pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_sfml->close();
		else if (event.type == sf::Event::KeyPressed)
			keyManager(event);
		else if (_type == GAME && event.type == sf::Event::Resized) {
			_sfml->getWindow().setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
			_sfml->setScreen({_sfml->getWindow().getSize().x - _sfml->getMargin().x, _sfml->getWindow().getSize().y});
		} else if (_type == GAME && event.type == sf::Event::MouseWheelScrolled)
			_sfml->mouseScrollEvent(event);
		else if (_type == GAME && event.type == sf::Event::MouseButtonPressed)
			mouseEvent(event, _move);
	}
	return (0);
}


void Graphical::Game::createIcon(const int &id, const float &x, const float &y, const Pos &margin, const float &padding)
{
	auto &player = _sfml->getBlock(id);
	player->setScale(static_cast<float>(margin.x) / player->getTexture()->getSize().x,
					 static_cast<float>(margin.x) / player->getTexture()->getSize().y);
	player->setPosition(x, y * padding);
	_sfml->getWindow().draw(*player);
}

sf::FloatRect Graphical::Game::createFilter(const int &id, const float &x, const float &y, const Pos &margin, const float &padding)
{
	sf::Color color = (_filters[id] ? sf::Color::Green : sf::Color::Red);
	auto &player = _sfml->getBlock(id);
	player->setScale(static_cast<float>(margin.x) / player->getTexture()->getSize().x,
					 static_cast<float>(margin.x) / player->getTexture()->getSize().y);
	player->setPosition(x, y * padding);
	sf::Color last = player->getColor();
	player->setColor(color);
	_sfml->getWindow().draw(*player);
	player->setColor(last);
	return (player->getGlobalBounds());
}

void Graphical::Game::initFilters()
{
	_filters[13] = false;
	_filters[11] = true;
	_filters[2] = true;
	_filters[7] = true;
	_filters[8] = true;
	_filters[12] = false;
}

std::map<int, sf::FloatRect> Graphical::Game::printFilters()
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 6;
	Pos margin = _sfml->getMargin();
	margin.x /= 2;
	float x = _sfml->getWindow().getSize().x - margin.x;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

	buttons[13] = createFilter(13, x, y, margin, padding);
	y += 1;
	buttons[11] = createFilter(11, x, y, margin, padding);
	y += 1;
	buttons[2] = createFilter(2, x, y, margin, padding);
	y += 1;
	buttons[7] = createFilter(7, x, y, margin, padding);
	y += 1;
	buttons[8] = createFilter(8, x, y, margin, padding);
	y += 1;
	buttons[12] = createFilter(12, x, y, margin, padding);
	return buttons;
}

long Graphical::Game::eventFilters(const std::map<int, sf::FloatRect> &buttons)
{
	long result = 0;
	sf::Vector2f position(sf::Mouse::getPosition(_sfml->getWindow()));

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return 0;
	for (auto &button : buttons) {
		if (button.second.contains(position)) {
			_filters[button.first] = !_filters[button.first] && true;
			result = 300000000; // antispam
		}
	}
	if (_filters[13]) {
		_type = MENU;
		_filters[13] = false;
	}
	if (_filters[12]) {
		for (auto &filter : _filters)
			if (filter.first != 13)
				filter.second = true;
		_filters[12] = false;
	}
	return result;
}

void Graphical::Game::printInventoryCases()
{
	std::map<int, sf::FloatRect> buttons;
	const std::size_t filterNb = 10;
	Pos margin = _sfml->getMargin();
	float x = _sfml->getWindow().getSize().x - margin.x;
	margin.x /= 2;
	float padding = static_cast<float>(_sfml->getWindow().getSize().y) / filterNb;
	float y = 0;

	createIcon(15, x, y, margin, padding);
	createIcon(14, x, y, margin, padding);
	y +=1;
	while (y < 10) {
		createIcon(15, x, y, margin, padding);
		y += 1;
	}
}

void Graphical::Game::printToolbar()
{
	auto &player = _sfml->getBlock(16);
	player->setScale(_sfml->getMargin().x, _sfml->getWindow().getSize().y);
	player->setPosition(_sfml->getWindow().getSize().x - _sfml->getMargin().x, 0);
	_sfml->getWindow().draw(*player);
}

void Graphical::Game::printGame()
{
	printToolbar();
	printInventoryCases();
	printMap(_map->getMap());
	auto buttons = printFilters();
	static long last = 0;


	std::chrono::system_clock::time_point time = std::chrono::system_clock::now();
	long now = time.time_since_epoch().count() ;

	if (now > last) {
		auto antiSpam = eventFilters(buttons);
		if (antiSpam > 0)
			last = now + antiSpam;
	}
}

int Graphical::Game::loop()
{
	_sfml->open(Graphical::Sfml::WINDOW);
	_sfml->createBlocks();
	initFilters();
	while (_sfml->isOpen() && _com->isValidFd(_com->getSocket())) {
		manageEvent();
		readServer();
		_sfml->clear();
		switch (_type) {
			case MENU: printMenu(); break;
			case GAME: printGame(); break;
			case EXIT: _sfml->close();
			default: break;
		}
		_sfml->display();
	}
	return (0);
}

void Graphical::Game::initCommunication(const std::string &team)
{
	if (!_com->sendToFd(_com->getSocket(), team))
		throw std::logic_error("Server is closed.");
	if (!_com->sendToFd(_com->getSocket(), "msz")) {
		throw std::logic_error("Server is closed.");
	}
};

int main(int ac, char **av)
{
	if (ac != 3 || av[1] == nullptr || av[2] == nullptr)
		return (std::cerr << "I need a port and a team argument" << std::endl, 84);
	Graphical::Game game;

	game.initPtrFunction();
	game.setCommunication(std::make_unique<Graphical::Communication>(std::stoi(av[1])));
	game.setGraphicTeam(av[2]);
	//game.initCommunication(av[2]);
	game.setDisplayer(std::make_unique<Graphical::Sfml>());
	game.setMap(std::make_unique<Graphical::Map>());
	game.loop();
	return (0);
}

