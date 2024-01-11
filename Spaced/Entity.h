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
	float speed_mult;
	bool isNegative;
	Equation() : pt(0), xt(0), yt(0), m_xt(0), m_yt(0), x_max(0), speed_mult(1), isNegative(false) {};
	Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x_max, float speed_mult, bool reverse);
};


class Entity {
protected:
	sf::Sprite sprite;
	std::vector<Equation> eqs;
	float speed;
	float pos_x;
public:
	Entity() : speed(0), pos_x(0) {}
	Entity(sf::Texture& texture, float pos_x, float speed);
	void setRotation(float r);
	void setPos_x(float pos_x);
	void setSpeed(float speed);
	void setScale(float s1, float s2);
	void setPosition(float x, float y);
	void setEqs(std::vector<Equation> eqs);
	void setTexture(sf::Texture& texture);
	float getSpeed();
	float getPos_x();
	sf::Sprite getSprite();
	sf::Vector2f getScale();
	sf::Vector2f getPosition();
	std::vector<Equation> getEqs();
	sf::FloatRect getGlobalBounds();
	void push_back(Equation eq);
	void update(float time);
};



class GameEntity : public Entity {
protected:
	int health;
public:
	GameEntity() : health(0) {};
	GameEntity(sf::Texture& texture, float pos_x, float speed, int health);
	void setHealth(int health);
	int getHealth();
};



class Player : public GameEntity {
protected:
	sf::Clock attack1_clock;
	sf::Clock attack2_clock;
public:
	Player() {};
	Player(sf::Texture& texture, float pos_x, float speed, int health);
	void move(float time);
	void keepInBoundary(sf::FloatRect boundary);
	bool attack(int type);
};


class Enemy : public GameEntity {
protected:
	sf::Clock attack_clock;
public:
	Enemy() {}
	virtual bool attack() { return false; };
};


class Enemy0 : public Enemy {
public:
	Enemy0() {}
	Enemy0(sf::Texture& texture, float pos_x);
	bool attack();
};