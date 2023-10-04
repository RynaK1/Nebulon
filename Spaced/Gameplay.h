#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Player.h"
#include "Game.h"

class Gameplay {
private:
	sf::Texture player_t;
	Game game;
	EnemyManager enemyManager;
	Player player;
	bool fhd;
public:
	Gameplay();
	int display(sf::RenderWindow &window);
};