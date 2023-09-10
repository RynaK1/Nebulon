#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "Externs.h"

class Player {
private:
	sf::Texture texture;
	sf::Sprite sprite;
	float mvmt_speed;
public:
	Player();
	sf::Sprite getSprite();
	void shoot();
	void move(float time);
};