#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Externs.h"
#include "EnemyManager.h"
#include "Player.h"
#include "Game.h"

class Gameplay {
private:
public:
	int display(sf::RenderWindow &window);
};