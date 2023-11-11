#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <map>

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
	bool boss_flag;
	sf::Clock clock; 
	sf::Clock boss_clock;
	std::map<std::string, sf::Texture> textures;
public:
	Stage() : fhd(false), MIN(-1000), MAX(10000), s1flags{0,0,0} {}
	Stage(std::map<std::string, sf::Texture>* textures,  bool fhd);
	std::vector<Enemy*> spawn(int stage);
	void del();
};