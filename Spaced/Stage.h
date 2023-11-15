#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include "Enemy.h"

struct EnemyMvmt {
	float MIN;
	float MAX;
	std::vector<Movement> e0Mvmts;
	std::vector<Movement> e1Mvmts;
	std::vector<Movement> eBossMvmts;
	EnemyMvmt() : MIN(-1000), MAX(10000) {}
	EnemyMvmt(float speed, bool fhd);
};


class Stage {
private:
	bool fhd;
	float MIN;
	float MAX;
	EnemyMvmt enemyMvmt;
	bool eflags[10];
	bool boss_flag;
	sf::Clock clock; 
	sf::Clock boss_clock;
	std::map<std::string, sf::Texture> textures;
public:
	Stage() : fhd(false), MIN(-1000), MAX(10000), boss_flag(false), eflags{0,0,0,0,0,0,0,0,0,0} {}
	Stage(std::map<std::string, sf::Texture>* textures,  bool fhd);
	std::vector<Enemy*> spawn(int stage);
	void reset();
	void load(int stage);
	void bossMovement();
};