#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Externs.h"

class Menu {
private:
public:
	int displayMainMenu(sf::RenderWindow &window, sf::Music& music);
	void displayOptions(sf::RenderWindow &window, sf::Music& music);
};