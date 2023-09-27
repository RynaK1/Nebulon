#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>

#include "Externs.h"


class BackEntity {
private:
	sf::Sprite sprite;
	Equation equation;
	float speed;
public:
	BackEntity(Equation eq, sf::Texture& texture, bool fhd, float scale, float s);
	void setRotation(float r);
	void setPosition(float x, float y);
	void setScale(float s1, float s2);
	sf::Vector2f getScale();
	sf::FloatRect getGlobalBounds();
	void setEqX(float x);
	float getSpeed();
	sf::Sprite getSprite();
	Equation getEquation();
};


class BackEntityManager {
private:
	sf::Clock clock;
	std::vector<BackEntity> backEntities;
	bool fhd;
	int backEntities_size;
	bool flags[3];
public:
	BackEntityManager() {}
	BackEntityManager(bool fhd);
	int getBackEntities_size();
	std::vector<BackEntity> getBackEntities();
	void spawn(sf::Texture* backEntities_t);
	void updateBackEntities(float time);
	void removeBackEntity(int i);
};

// USE A CLOCK TO TRACK WHEN ENTITIES SHOULD SPAWN
// FIND ALL SPRITES TO USE