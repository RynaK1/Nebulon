#pragma once

#include <SFML\Graphics.hpp>
#include<array>

#include "Enemy.h"
#include "Player.h"

class Game {
private:
public:
	std::array<bool, 4> checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size);
	std::array<bool, 2> updateCollisions(EnemyManager& em, Player& player);
};