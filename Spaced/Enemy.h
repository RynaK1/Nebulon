#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Externs.h"
#include "Movement.h"

/*
class Enemy {
protected:
	sf::Sprite sprite;
	Movement mvmt;
	int health;
	int type;
public:
	Enemy() : type(0), health(0) {};
	void setPosition(float x, float y);
	void setHealth(int health);
	int getHealth();
	int getType();
	sf::Vector2f update();
	sf::FloatRect getGlobalBounds();
	sf::Sprite getSprite();
	void attack();
};


class EnemyT1 : public Enemy {
private:
public:
	void attack();
	EnemyT1(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyT2 : public Enemy {
private:
public:
	void attack();
	EnemyT2(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyBoss : public Enemy {
private:
public:
	void attack();
	EnemyBoss(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyManager {
private:
	std::vector<Enemy> enemies;
	bool fhd;
	int enemies_size;
public:
	EnemyManager();
	void setEnemyHealth(int health, int index);
	int getEnemies_size();
	std::vector<Enemy> getEnemies();
	void spawn(Movement mvmt, sf::Texture& texture, int type);
	void updateEnemies(float time);
	void removeEnemy(int index);
};
*/