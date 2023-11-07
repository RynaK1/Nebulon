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



class SmallBullet : public Bullet {
private:
public:
	SmallBullet(sf::Texture& texture, bool fhd);
};



class LargeBullet : public Bullet {
private:
public:
	LargeBullet(sf::Texture& texture, bool fhd);
};


class EnemyBullet : public Bullet {
private:
public:
	EnemyBullet(sf::Texture& texture, bool fhd);
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
	void update(float time);
	void remove(int i);
};