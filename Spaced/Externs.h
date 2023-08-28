#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

const static int GO_MENU = 0;
const static int GO_GAMEPLAY = 1;
const static int GO_END = 2;
const static int GO_HIGHSCORE = 3;
const static int QUIT = -1;


inline bool buttonBounds(sf::Vector2i mousePos, sf::Text text) {
	sf::FloatRect bound = text.getGlobalBounds();
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}

inline bool buttonBounds(sf::Vector2i mousePos, sf::RectangleShape shape) {
	sf::FloatRect bound = shape.getGlobalBounds();
	bound.top -= 13;
	bound.height += 20;
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}