#include "Stage.h"

Stage::Stage(bool fhd, sf::Texture* textures) {
	this->fhd = fhd;

	int s1flags_size = sizeof(s1flags);
	for (int i = 0; i < s1flags_size; i++) {
		s1flags[i] = false;
	}

	enemyMvmt = EnemyMvmt(fhd);
	this->textures = textures;
}


std::vector<Enemy> Stage::spawn(int stage) {
	std::vector<Enemy> spwn;

	int time = (int)clock.getElapsedTime().asSeconds();
	switch (stage) {
	case 1: 
		if (s1flags[0] == false && time == 1) {
			Enemy0 enemy0(enemyMvmt.e0Mvmts[std::rand() % 2], textures[0], fhd);
			spwn.push_back(enemy0);
			s1flags[0] = true;
		}
		else if (s1flags[1] == false && time == 3) {
			Enemy1 enemy1(enemyMvmt.e1Mvmts[std::rand() % 2], textures[1], fhd);
			spwn.push_back(enemy1);
			EnemyBoss enemyBoss(enemyMvmt.eBossMvmts[0], textures[2], fhd);
			spwn.push_back(enemyBoss);
			s1flags[1] = true;
		}
		else if (time == 5) {
			int s1flags_size = sizeof(s1flags);
			for (int i = 0; i < s1flags_size; i++) {
				s1flags[i] = false;
			}
			clock.restart();
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}

	return spwn;
}


EnemyMvmt::EnemyMvmt(bool fhd) {
	MIN = -1000;
	MAX = 10000;

	Equation eq0(3, -150, -350, 0.25f, 0.005f, MIN, 70, true, fhd);
	Movement mvmt0(764.5f, fhd);
	mvmt0.push_back(eq0);
	e0Mvmts.push_back(mvmt0);

	Equation eq1(3, -200, -400, 0.25f, 0.005f, MIN, 70, true, fhd);
	Movement mvmt1(764.5f, fhd);
	mvmt1.push_back(eq1);
	e0Mvmts.push_back(mvmt1);

	Equation eq2(3, -150, -350, 0.25f, 0.005f, MIN, 70, true, fhd);
	Movement mvmt2(764.5f, fhd);
	mvmt2.push_back(eq2);
	e1Mvmts.push_back(mvmt2);

	Equation eq3(3, -200, -400, 0.25f, 0.005f, MIN, 70, true, fhd);
	Movement mvmt3(764.5f, fhd);
	mvmt3.push_back(eq3);
	e1Mvmts.push_back(mvmt3);

	Equation eq4(3, -200, -400, 0.25f, 0.005f, MIN, 70, true, fhd);
	Movement mvmt4(764.5f, fhd);
	mvmt4.push_back(eq4);
	eBossMvmts.push_back(mvmt4);
}