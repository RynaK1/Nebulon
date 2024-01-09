#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <array>
#include <iostream>

struct Equation {
	float pt;
	float xt;
	float yt;
	float m_xt;
	float m_yt;
	float x_max;
	bool negative;
	float speed_mult;
	Equation() : pt(0), xt(0), yt(0), m_xt(0), m_yt(0), x_max(0), speed_mult(1), negative(false) {};
	Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x_max, float speed_mult, bool reverse);
};


class Entity {
protected:
	sf::Sprite sprite;
	std::vector<Equation> eqs;
	short eq_curr;
	float speed;
	float pos_x;
public:
	Entity() : eq_curr(0), speed(0), pos_x(0) {}
	Entity(sf::Texture& texture, float pos_x, float speed);
	void setEqs(std::vector<Equation> eqs);
	void setRotation(float r);
	void setPos_x(float pos_x);
	void setPosition(float x, float y);
	void setScale(float s1, float s2);
	void setSpeed(float speed);
	sf::Vector2f getScale();
	sf::Sprite getSprite();
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();
	float getSpeed();
	std::vector<Equation> getEqs();
	float getPos_x();
	void push_back(Equation eq);
	sf::Vector2f update(float time);
};


class EntityManager {
private:
	sf::Clock clock;
	std::vector<Entity> entities;
	sf::IntRect boundary;
	int size;
public:
	EntityManager() : size(0) {};
	EntityManager(bool fhd);
	int getSize();
	std::vector<Entity> getEntities();
	void setRotation(int i, float num);
	void remove(int i);
	void spawn(Entity me);
	void update(float time);
};