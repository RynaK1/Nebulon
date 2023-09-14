#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <cmath>

#include "Externs.h"

struct Equation {
	float pwr;
	float horiz;
	float vert;
	float mult_vert;
	float mult_horiz;
	float x;
};


class Enemy {
protected:
	sf::Sprite sprite;
	Equation mvmt;
	int type;
public:
	void setEqX(float x);
	int getType();
	Equation getMvmt();
	sf::Sprite& getSprite();
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
	std::string res;
	int enemies_size;
public:
	EnemyManager();
	int getEnemies_size();
	std::vector<Enemy> getEnemies();
	void spawn(int type, Equation mv);
	void updateEnemies(float time);
};