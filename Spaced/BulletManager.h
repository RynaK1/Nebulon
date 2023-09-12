#pragma once

#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>

#include "Externs.h"

class BulletManager {
private:
	std::vector<sf::Sprite> bullets;
	std::string res;
	sf::Texture bullet_t;
	sf::Sprite bullet;
	int bullets_size;
public:
	BulletManager();
	std::vector<sf::Sprite> getBullets();
	int getBullets_size();
	void shoot(sf::FloatRect pos);
	void update();
};