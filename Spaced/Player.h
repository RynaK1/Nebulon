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
	int health;
	sf::Clock shootCD;
	sf::Clock damagedCD;
public:
	Player();
	void setHealth(int health);
	int getHealth();
	sf::Sprite getSprite();
	BulletManager getBulletManager();
	void shoot();
	void updateBullets(float time);
	void removeBullet(int index);
	void move(float time, std::array<bool, 4> bounds);
	void playerDamaged(int dmg);
};