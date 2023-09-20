#pragma once

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Externs.h"

class Bullet {
protected:
	sf::Sprite sprite;
	int damage;
	int speed;
	int type;
public:
	Bullet();
	void setScale(float x, float y);
	void setPosition(float x, float y);
	int getDamage();
	int getType();
	int getSpeed();
	sf::Sprite getSprite();
	sf::FloatRect getGlobalBounds();
	void move(float offsetX, float offsetY);
};



class smallBullet : public Bullet {
private:
public:
	smallBullet(sf::Texture& texture, bool fhd);
};



class largeBullet : public Bullet {
private:
public:
	largeBullet(sf::Texture& texture, bool fhd);
};



class BulletManager {
private:
	bool fhd;
	int num_bullets;
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	std::vector<Bullet> bullets;
public:
	BulletManager();
	std::vector<Bullet> getBullets();
	void shoot(sf::Texture& texture, sf::FloatRect pos, int type);
	void updateBullets(float time);
	void removeBullet(int index);
};