#pragma once

#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Externs.h"

class BulletManager {
private:
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
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
	void updateBullets(float time);
	void removeBullet(int index);
};