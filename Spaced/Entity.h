#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>

#include "Movement.h"


class Entity {
protected:
	sf::Sprite sprite;
public:
	Entity() {}
	Entity(sf::Texture& texture);
	void setRotation(float r);
	void setPosition(float x, float y);
	void setScale(float s1, float s2);
	sf::Sprite getSprite();
	sf::Vector2f getScale();
	sf::FloatRect getGlobalBounds();
};


class MovingEntity : public Entity {
protected:
	Movement mvmt;
public:
	MovingEntity() {}
	MovingEntity(Movement mvmt, sf::Texture& texture, float scale, bool fhd);
	void setMvmt(Movement mvmt);
	sf::Vector2f update(float time);
};


class MovingEntityManager {
private:
	sf::Clock clock;
	std::vector<MovingEntity> movingEntities;
	bool fhd;
	int movingEntities_size;
	bool flags[3];
public:
	MovingEntityManager() : fhd(false), movingEntities_size(0), flags{false, false, false} {};
	MovingEntityManager(bool fhd);
	int getMovingEntities_size();
	std::vector<MovingEntity> getMovingEntities();
	void update(float time);
	void remove(int i);
	void spawn(MovingEntity me);
};