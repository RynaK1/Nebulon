#pragma once

#include <SFML\Graphics.hpp>
#include<array>

#include "EnemyManager.h"
#include "Player.h"

class Game {
private:
public:
	std::array<bool, 4> checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size);
	bool checkPlayerCollision(Player player, EnemyManager em);
	bool checkEnemyCollision(Enemy e, BulletManager bm);
};