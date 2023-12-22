#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>

#include "Movement.h"


class Entity {
protected:
	sf::Sprite sprite;
	Movement mvmt;
public:
	Entity() {}
	Entity(Movement mvmt, sf::Texture& texture);
	void setMvmt(Movement mvmt);
	void setRotation(float r);
	void setPosition(float x, float y);
	void setScale(float s1, float s2);
	sf::Vector2f getScale();
	sf::Sprite getSprite();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f update(float time);
};


class EntityManager {
private:
	sf::Clock clock;
	std::vector<Entity> entities;
	bool fhd;
	int size;
public:
	EntityManager() : fhd(false), size(0) {};
	EntityManager(bool fhd);
	int getSize();
	std::vector<Entity> getEntities();
	void setRotation(int i, float num);
	void remove(int i);
	void spawn(Entity me);
	void update(float time);
};