#pragma once

#include <SFML\Graphics.hpp>

#include "Externs.h"

class Menu {
private:
public:
	int displayMainMenu(sf::RenderWindow &window);
	int displayOptions(sf::RenderWindow &window);
};