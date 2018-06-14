//
// EPITECH PROJECT, 2018
// arcade
// File description:
// sfml class
//

#include "Sfml.hpp"

void Graphical::Sfml::resetView()
{
	sf::View view = _screen.getView();

	_zoom = 1;
	view.setSize(_window.getSize().x, _window.getSize().y);
	_screen.setView(view);
}

void Graphical::Sfml::mouseScrollEvent(sf::Event &event)
{
	sf::View view = _screen.getView();

	if (event.mouseWheelScroll.delta > 0)
		_zoom = 1.1f;
	else if (event.mouseWheelScroll.delta < 0) {
		/*if (_screen.getView().getSize().x > _window.getSize().x &&
			_screen.getView().getSize().y > _window.getSize().y)
			return resetView();*/
		_zoom = 0.9f;
	}
	view.zoom(_zoom);
	_screen.setView(view);
}

void Graphical::Sfml::mouseEvent(sf::Event &event)
{
	(void) event;
	sf::View view = _screen.getView();
	sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (!(mousePos.x > 0 &&
			  mousePos.y > 0 &&
			  mousePos.x < static_cast<int>(_window.getSize().x - _margin.x) &&
			  mousePos.y < static_cast<int>(_window.getSize().y)))
			return;
		mousePos.x = static_cast<int>(
				(mousePos.x / static_cast<float>(_screen.getSize().x)) *
				(view.getSize().x));
		mousePos.y = static_cast<int>(
				(mousePos.y / static_cast<float>(_screen.getSize().y)) *
				(view.getSize().y));
		mousePos.x = static_cast<int>(mousePos.x - (view.getSize().x / 2));
		mousePos.y = static_cast<int>(mousePos.y - (view.getSize().y / 2));
		view.move(mousePos.x, mousePos.y);
	} else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		view.setCenter((_window.getSize().x - _margin.x) / 2.0f, _window.getSize().y / 2.0f);
	}
	_screen.setView(view);
}