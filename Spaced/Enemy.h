#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "Movement.h"

class Enemy : public MovingEntity {
protected:
	sf::Clock clock;
	int health;
	int value;
public:
	Enemy() : value(0), health(0) {};
	void setHealth(int health);
	void attack() {}
	int getHealth();
	int getValue();
};


class Enemy0 : public Enemy {
private:
public:
	void attack();
	Enemy0() {}
	Enemy0(Movement mvmt, sf::Texture& texture, bool fhd);
};


class Enemy1 : public Enemy {
private:
public:
	void attack();
	Enemy1() {}
	Enemy1(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyBoss : public Enemy {
private:
public:
	void attack();
	EnemyBoss() {}
	EnemyBoss(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyManager {
private:
	std::vector<Enemy> enemies;
	bool fhd;
	int enemies_size;
public:
	EnemyManager() : fhd(0), enemies_size(0) {};
	EnemyManager(bool fhd);
	void setEnemyHealth(int health, int index);
	Enemy getEnemy(int i);
	int getEnemies_size();
	std::vector<Enemy> getEnemies();
	void spawn(Enemy enemy);
	void update(float time);
	void remove(int index);
};