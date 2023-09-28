#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>

#include "Externs.h"


class Entity {
protected:
	sf::Sprite sprite;
	bool fhd;
public:
	Entity();
	void setRotation(float r);
	void setPosition(float x, float y);
	void setScale(float s1, float s2);
	sf::Sprite getSprite();
	sf::Vector2f getScale();
	sf::FloatRect getGlobalBounds();
};


class MovingEntity : public Entity {
private:
	Equation equation;
	float speed;
public:
	MovingEntity(Equation eq, sf::Texture& texture, bool fhd, float scale, float speed);
	void setEqX(float x);
	float getSpeed();
	Equation getEquation();
};


class MovingEntityManager {
private:
	sf::Clock clock;
	std::vector<MovingEntity> movingEntities;
	bool fhd;
	int movingEntities_size;
	bool flags[3];
public:
	MovingEntityManager();
	MovingEntityManager(bool fhd);
	int getMovingEntities_size();
	std::vector<MovingEntity> getMovingEntities();
	void spawn(sf::Texture* back1s_t);
	void updateMovingEntities(float time);
	void removeMovingEntity(int i);
};

// USE A CLOCK TO TRACK WHEN ENTITIES SHOULD SPAWN
// FIND ALL SPRITES TO USE