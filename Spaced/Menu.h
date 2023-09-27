#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Externs.h"
#include "BackEntityManager.h"


class Menu {
private:
public:
	int displayMainMenu(sf::RenderWindow& window, sf::Music& music, sf::Sound& sfx, BackEntityManager& backEntityManager, std::array<sf::Texture, 10>& backEntities_t);
	int displayOptions(sf::RenderWindow& window, sf::Music& music, sf::Sound& sfx, BackEntityManager& backEntityManager, std::array<sf::Texture, 10>& backEntities_t);
};