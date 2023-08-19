#pragma once

#include <SFML\Graphics.hpp>

const static int GO_MENU = 0;
const static int GO_GAMEPLAY = 1;
const static int GO_END = 2;
const static int GO_HIGHSCORE = 3;
const static int QUIT = -1;

inline bool buttonBounds(sf::Vector2i mousePos, int x_left, int x_right, int y_top, int y_bottom) {
	if (mousePos.x > x_left && mousePos.x < x_right && mousePos.y > y_top && mousePos.y < y_bottom) {
		return true;
	}
	return false;
}