#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Externs.h"

class Enemy {
protected:
	sf::Sprite sprite;
	Equation mvmt;
	int health;
	int type;
public:
	Enemy();
	void setSprite(sf::Sprite sprite);
	void setEqX(float x);
	int getHealth();
	int getType();
	Equation getMvmt();
	sf::Sprite& getSprite();
	void setHealth(int health);
	void attack();
};


class EnemyT1 : public Enemy {
private:
public:
	void attack();
	EnemyT1(Equation mv);
};


class EnemyT2 : public Enemy {
private:
public:
	void attack();
	EnemyT2(Equation mv);
};


class EnemyBoss : public Enemy {
private:
public:
	void attack();
	EnemyBoss(Equation mv);
};


class EnemyManager {
private:
	sf::Texture enemy_t1;
	sf::Texture enemy_t2;
	sf::Texture enemy_boss;
	std::vector<Enemy> enemies;
	bool fhd;
	int enemies_size;
public:
	EnemyManager();
	void setEnemyHealth(int health, int index);
	int getEnemies_size();
	std::vector<Enemy> getEnemies();
	void spawn(int type, Equation eq);
	void updateEnemies(float time);
	void removeEnemy(int index);
};