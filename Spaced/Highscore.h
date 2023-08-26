#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Externs.h"

class Highscore {
private:
public:
	int display(sf::RenderWindow &window, sf::Music& music);
};