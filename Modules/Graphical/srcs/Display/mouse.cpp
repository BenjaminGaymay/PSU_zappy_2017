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

	if (event.mouseWheelScroll.delta > 0) {
		_zoom = 1.1f;
		_zoomRank += 0.1f;
	}
	else if (event.mouseWheelScroll.delta < 0) {
		/*if (_screen.getView().getSize().x > _window.getSize().x &&
			_screen.getView().getSize().y > _window.getSize().y)
			return resetView();*/
		_zoom = 0.9f;
		_zoomRank -= 0.1f;
	}
	view.zoom(_zoom);
	_screen.setView(view);
}