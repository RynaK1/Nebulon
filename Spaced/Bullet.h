#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Externs.h"

class Bullet {
protected:
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	sf::Texture texture;
	sf::Sprite sprite;
	int damage;
	int speed;
	int type;
public:
	Bullet();
	void setPosition(float x, float y);
	int getSpeed();
	sf::Sprite getSprite();
	sf::FloatRect getGlobalBounds();
	void move(float offsetX, float offsetY);
};


class smallBullet : public Bullet {
private:
public:
	smallBullet(bool fhd);
};


class largeBullet : public Bullet {
private:
public:
	largeBullet(bool fhd);
};