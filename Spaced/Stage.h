#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>

#include "Enemy.h"

struct EnemyMvmt {
	float MIN;
	float MAX;
	std::vector<Movement> e0Mvmts;
	std::vector<Movement> e1Mvmts;
	std::vector<Movement> eBossMvmts;
	EnemyMvmt() : MIN(-1000), MAX(10000) {}
	EnemyMvmt(bool fhd);
};


class Stage {
private:
	bool fhd;
	float MIN;
	float MAX;
	EnemyMvmt enemyMvmt;
	bool s1flags[10];
	sf::Clock clock;   
	sf::Texture* textures;
public:
	Stage() : fhd(false), MIN(-1000), MAX(10000), textures(nullptr), s1flags{0,0,0} {}
	Stage(bool fhd, sf::Texture* textures);
	std::vector<Enemy> spawn(int stage);
	void del();
};