#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include "Entity.h"

/*
struct EnemyEqs {
	float MIN;
	float MAX;
	std::vector<std::vector<Equation>> e0Eqs;
	std::vector<std::vector<Equation>> e1Eqs;
	std::vector<std::vector<Equation>> eBossEqs;
	EnemyEqs() : MIN(-1000), MAX(10000) {}
	EnemyEqs(float speed_up);
};


class Stage {
private:
	bool fhd;
	float MIN;
	float MAX;
	EnemyEqs enemyEqs; 
	bool eflags[15];
	bool boss_flag;
	sf::Clock clock; 
	sf::Clock boss_clock;
	std::map < std::string, Enemy> enemies;
	std::map<std::string, sf::Texture> textures;
public:
	Stage() : fhd(false), MIN(-1000), MAX(10000), boss_flag(false), eflags{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} {}
	Stage(std::map<std::string, sf::Texture>* textures,  bool fhd);
	void update();
	void spawn(int stage);
	void reset();
	void load(int stage);
};
*/