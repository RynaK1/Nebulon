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
	EnemyFactory enemyFactory;
	std::map<std::string, sf::Texture> textures;
	sf::Clock boss_clock;
	sf::Clock clock;
	EnemyEqs enemyEqs;
	float MIN;
	float MAX;
	int stage_num;
	bool enemy_spawned[15];
	bool boss_spawned;
public:
	Stage() : MIN(-1000), MAX(10000), boss_spawned(false), stage_num(0), enemy_spawned{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} {}
	Stage(std::map<std::string, sf::Texture>& textures);
	int getStage_num();
	void spawn(std::vector<Enemy*>* enemies);
};