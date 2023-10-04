#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Player.h"
#include "Enemy.h"

class Gameplay {
private:
	sf::Texture player_t;
	EnemyManager enemyManager;
	Player player;
	bool fhd;
public:
	Gameplay();
	int display(sf::RenderWindow &window);
	std::array<bool, 4> checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size);
	std::array<bool, 2> updateCollisions(EnemyManager& em, Player& player);
};