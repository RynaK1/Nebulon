#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Externs.h"

class Enemy {
protected:
	sf::Sprite sprite;
	Equation equation;
	int health;
	int type;
public:
	Enemy();
	void setPosition(float x, float y);
	void setHealth(int health);
	void setEqX(float x);
	int getHealth();
	int getType();
	sf::FloatRect getGlobalBounds();
	Equation getEquation();
	sf::Sprite getSprite();
	void attack();
};


class EnemyT1 : public Enemy {
private:
public:
	void attack();
	EnemyT1(Equation eq, sf::Texture& texture, bool fhd);
};


class EnemyT2 : public Enemy {
private:
public:
	void attack();
	EnemyT2(Equation eq, sf::Texture& texture, bool fhd);
};


class EnemyBoss : public Enemy {
private:
public:
	void attack();
	EnemyBoss(Equation eq, sf::Texture& texture, bool fhd);
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
	void spawn(Equation eq, sf::Texture& texture, int type);
	void updateEnemies(float time);
	void removeEnemy(int index);
};