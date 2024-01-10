#pragma once


#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Entity.h"
#include "BulletManager.h"

/*
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
	sf::Texture* attack_texture;
public:
	void attack();
	Enemy0() : attack_texture(nullptr) {}
	Enemy0(sf::Texture& texture, sf::Texture& attack_texture);
};


class Enemy1 : public Enemy {
private:
	sf::Texture* attack_texture;
public:
	Enemy1() {}
	Enemy1(sf::Texture& texture, sf::Texture& attack_texture);
};


class EnemyBoss : public Enemy {
private:
	sf::Texture* attack_texture;
public:
	void attack();
	EnemyBoss() {}
	EnemyBoss(sf::Texture& texture, sf::Texture& attack_texture);
};


/*
class EnemyManager {
private:
	std::vector<Enemy> enemies;
	sf::IntRect boundary;
	int enemies_size;
public:
	EnemyManager() : enemies_size(0) {};
	EnemyManager(bool fhd);
	void setEnemyHealth(int health, int index);
	Enemy getEnemy(int i);
	int getEnemies_size();
	std::vector<Enemy> getEnemies();
	void push_back(Enemy enemy);
	void update(float time);
	void remove(int i);
};
*/