#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <map>

#include "Entity.h"


struct EnemyEqs {
	float MIN;
	float MAX;
	std::vector<std::vector<Equation>> e0Eqs;
	std::vector<std::vector<Equation>> e1Eqs;
	std::vector<std::vector<Equation>> eBossEqs;
	std::vector<float> e0Eqs_startPos;
	std::vector<float> e1Eqs_startPos;
	std::vector<float> eBossEqs_startPos;
	size_t e0Eqs_size;
	size_t e1Eqs_size;
	size_t eBossEqs_size;
	EnemyEqs();
};


class Stage {
private:
	float MIN;
	float MAX;
	int stage_num;
	EnemyEqs enemyEqs; 
	bool eflags[15];
	bool boss_flag;
	sf::Clock clock; 
	sf::Clock boss_clock;
	std::map<std::string, sf::Texture> textures;
public:
	Stage() : MIN(-1000), MAX(10000), boss_flag(false), stage_num(0), eflags{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} {}
	Stage(std::map<std::string, sf::Texture>& textures);
	void spawn(std::vector<GameEntity*>* entities);
};