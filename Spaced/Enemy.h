#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "Movement.h"
#include "BulletManager.h"

class Enemy : public Entity {
protected:
	sf::Clock clock;
	BulletManager bulletManager;
	int health;
	int value;
	bool flag;
	bool boss;
public:
	Enemy() : value(0), health(0), flag(false), boss(false) {};
	void setHealth(int health);
	BulletManager* getBulletManager();
	int getHealth();
	int getValue();
	bool isBoss();
	void updateBullets(float time);
	virtual void attack(sf::Texture& texture) {}
};


class Enemy0 : public Enemy {
private:
public:
	void attack(sf::Texture& texture);
	Enemy0() {}
	Enemy0(Movement mvmt, sf::Texture& texture, bool fhd);
};


class Enemy1 : public Enemy {
private:
public:
	Enemy1() {}
	Enemy1(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyBoss : public Enemy {
private:
public:
	void attack(sf::Texture& texture);
	EnemyBoss() {}
	EnemyBoss(Movement mvmt, sf::Texture& texture, bool fhd);
};


class EnemyManager {
private:
	std::vector<Enemy*> enemies;
	bool fhd;
	int enemies_size;
public:
	EnemyManager() : fhd(0), enemies_size(0) {};
	EnemyManager(bool fhd);
	void setEnemyHealth(int health, int index);
	Enemy* getEnemy(int i);
	int getEnemies_size();
	std::vector<Enemy*> getEnemies();
	void spawn(Enemy* enemy);
	void update(float time, sf::Texture& textures);
	void remove(int i);
};