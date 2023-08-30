#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Externs.h"
#include "MenuBackend.h"


class Menu {
private:
public:
	int displayMainMenu(sf::RenderWindow &window, sf::Music& music);
	int displayOptions(sf::RenderWindow &window, sf::Music& music);
};