#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Externs.h"


class Menu {
private:
public:
	int displayMainMenu(sf::RenderWindow &window, sf::Music& music, sf::Music& sfx);
	int displayOptions(sf::RenderWindow &window, sf::Music& music, sf::Music& sfx);
};