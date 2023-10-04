#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "Movement.h"

class Enemy : public MovingEntity {
protected:
	int health;
	int type;
public:
	Enemy() : type(0), health(0) {};
	void setHealth(int health);
	int getHealth();
	int getType();
};


class EnemyT0 : public Enemy {
private:
public:
	void attack();
	EnemyT0(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyT1 : public Enemy {
private:
public:
	void attack();
	EnemyT1(Movement mvmt, sf::Texture& texture, bool fhd);
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
	EnemyManager() : fhd(0), enemies_size(0) {};
	EnemyManager(bool fhd);
	void setEnemyHealth(int health, int index);
	int getEnemies_size();
	std::vector<Enemy> getEnemies();
	void spawn(Movement mvmt, sf::Texture& texture, int type, float time);
	void update(float time);
	void remove(int index);
};