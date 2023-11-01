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
	std::vector<MovingEntity> movingEntities1;
	std::vector<MovingEntity> movingEntities2;
	bool fhd;
	int movingEntities1_size;
	int movingEntities2_size;
	bool flags[3];
public:
	MovingEntityManager() : fhd(false), movingEntities1_size(0), movingEntities2_size(0), flags{false, false, false} {};
	MovingEntityManager(sf::Texture* movingEntities_t, bool fhd);
	int getMovingEntities1_size();
	int getMovingEntities2_size();
	std::vector<MovingEntity> getMovingEntities1();
	std::vector<MovingEntity> getMovingEntities2();
	void update(float time);
	void remove1(int i);
	void remove2(int i);
	void spawn(sf::Texture* movingEntities_t);
};