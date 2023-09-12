#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <array>

#include "BulletManager.h"
#include "Externs.h"

class Player {
private:
	sf::Texture player_t;
	sf::Sprite player;
	BulletManager bulletManager;
	float mvmt_speed;
public:
	Player();
	sf::Sprite getSprite();
	BulletManager getBulletManager();
	void shoot();
	void update();
	void move(float time, std::array<bool, 4> bounds);
};