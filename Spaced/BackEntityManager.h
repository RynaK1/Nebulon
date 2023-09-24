#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

#include "Externs.h"


class BackEntity {
private:
	sf::Sprite sprite;
	Equation equation;
	float speed;
public:
	BackEntity(Equation eq, sf::Texture& texture, bool fhd, float scale, float s);
	void setPosition(float x, float y);
	sf::FloatRect getGlobalBounds();
	void setEqX(float x);
	float getSpeed();
	sf::Sprite getSprite();
	Equation getEquation();
};


class BackEntityManager {
private:
	std::vector<BackEntity> backEntities;
	bool fhd;
	int backEntities_size;
public:
	BackEntityManager();
	void spawn(Equation eq, sf::Texture& texture, float scale, float s);
	int getBackEntities_size();
	std::vector<BackEntity> getBackEntities();
	void updateBackEntities(float time);
	void removeBackEntity(int i);
};