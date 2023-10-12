#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <array>

#include "BulletManager.h"
#include "Externs.h"

class Player {
private:
	BulletManager bulletManager;
	sf::Sprite sprite;
	float mvmt_speed;
	int health;
	sf::Clock shoot1CD;
	sf::Clock shoot2CD;
	sf::Clock damagedCD;
	bool fhd;
public:
	Player() : mvmt_speed(0), health(0), fhd(false) {};
	Player(sf::Texture& texture, bool fhd);
	void setHealth(int health);
	int getHealth();
	sf::Sprite getSprite();
	std::vector<Bullet> getBullets();
	bool shoot(sf::Texture& texture, int type);
	void updateBullets(float time);
	void removeBullet(int index);
	void move(float time, std::array<bool, 4> bounds);
	void playerDamaged(int dmg);
	sf::FloatRect getGlobalBounds();
	float getCDPercent(int num);
};