#pragma once

#include <SFML\Graphics.hpp>

#include "Externs.h"

class Menu {
private:
public:
	int displayMainMenu(sf::RenderWindow &window);
	void displayOptions(sf::RenderWindow &window);
};