#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include <array>

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
	void move(float time, std::array<bool, 4> bounds);
};