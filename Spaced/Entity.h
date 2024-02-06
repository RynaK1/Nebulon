#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
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
public:
	Entity() : speed(0) {}
	Entity(sf::Texture& texture, float start_pos, float speed);
	void setRotation(float r);
	void setSpeed(float speed);
	void setScale(float s1, float s2);
	void setPosition(float x, float y);
	void setEqs(std::vector<Equation> eqs);
	void setTexture(sf::Texture& texture);
	float getSpeed();
	sf::Sprite getSprite();
	sf::Vector2f getScale();
	sf::Vector2f getPosition();
	std::vector<Equation> getEqs();
	sf::FloatRect getGlobalBounds();
	void push_back(Equation eq);
	void update(float time);
	float calcYPosition(float x);
};



class GameEntity : public Entity {
protected:
	int health;
	int dmg;
public:
	GameEntity() : health(0), dmg(0) {};
	GameEntity(sf::Texture& texture, float start_pos, float speed, int health, int dmg) :
		Entity(texture, start_pos, speed) {
		this->health = health;
		this->dmg = dmg;
	}
	void setHealth(int health);
	void setDmg(int dmg);
	int getHealth();
	int getDmg();
};



class Player : public GameEntity {
protected:
	sf::Clock attack1_clock;
	sf::Clock attack2_clock;
	sf::Clock hit_clock;
public:
	Player() {};
	Player(sf::Texture& texture, sf::Vector2f start_pos, float speed, int health);
	void move(float time);
	void hit(int dmg);
	void keepInBoundary(sf::FloatRect boundary);
	void attack(std::map<std::string, sf::Texture>& textures, std::vector<GameEntity*>* player_bullets);
	void death();
};



class Enemy : public GameEntity {
protected:
	bool isBoss;
	int attackType;
	sf::Clock attack_clock;
public:
	Enemy() : isBoss(false), attackType(0) {}
	Enemy(sf::Texture& texture, float start_pos, float speed, int health, int attackType, int dmg, bool isBoss) :
		GameEntity(texture, start_pos, speed, health, dmg) {
		this->attackType = attackType;
		this->isBoss = isBoss;
	}
	bool getIsBoss();
	void hit(int dmg);
	void attack(std::map<std::string, sf::Texture>& textures, std::vector<GameEntity*>* enemy_bullets);
};