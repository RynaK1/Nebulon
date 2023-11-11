#include "Stage.h"

Stage::Stage(std::map<std::string, sf::Texture>* textures, bool fhd) {
	this->fhd = fhd;
	this->textures = *textures;

	int s1flags_size = sizeof(s1flags);
	for (int i = 0; i < s1flags_size; i++) {
		s1flags[i] = false;
	}
	boss_flag = false;

	enemyMvmt = EnemyMvmt(fhd);
}


std::vector<Enemy*> Stage::spawn(int stage) {
	std::vector<Enemy*> spwn;
	int time = (int)clock.getElapsedTime().asSeconds();
	int boss_time = (int)clock.getElapsedTime().asSeconds();
	/*
	Creating stage
		- Create proper sized flag arr equating to the number of spawning instances within a cycle
		- Create if statement for appropriate timing
		- Create enemy with appropriate or randomized movement and texture
		- Push back created enemy to spwn
	*/

	if (boss_flag == false && boss_time == 1) {
		EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[0], textures["enemyBoss"], fhd);
		spwn.push_back(eBoss_0);
		boss_flag = true;
	}
	else if (boss_time == 240) {
		boss_flag = false;
		boss_clock.restart();
	}
	switch (stage) {
	case 1: 
		if (s1flags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			s1flags[0] = true;
		}
		else if (s1flags[1] == false && time == 3) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			s1flags[1] = true;
		}
		else if (s1flags[2] == false && time == 4) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			s1flags[2] = true;
		}
		else if (s1flags[3] == false && time == 5) {
			Enemy1* e1_2 =  new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			s1flags[3] = true;
		}
		else if (s1flags[4] == false && time == 6) {
			Enemy1*  e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			s1flags[4] = true;
		}
		else if (s1flags[5] == false && time == 7) {
			Enemy1* e1_4 =  new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			s1flags[5] = true;
		}
		else if (time == 10) {
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

/*
Creating new movement pattern
	- Create equation
	- Create movement
	- push to eMvmts with appropriate variable label
		- create new eMvmts vector for new enemy type
*/

EnemyMvmt::EnemyMvmt(bool fhd) {
	MIN = -1000;
	MAX = 10000;

	//pt, xt, yt, m_xt, m_yt, x_max, speed, reverse, fhd
	Equation e0_eq0(2, -150, -250, 0.25f, 0.005f, MAX, 100, false, fhd);
	Movement e0_m0(-15, fhd);
	e0_m0.push_back(e0_eq0);
	e0Mvmts.push_back(e0_m0);

	Equation e0_eq1(3, 67, -300, -0.07f, 0.001f, MAX, 100, false, fhd);
	Movement e0_m1(-15, fhd);
	e0_m1.push_back(e0_eq1);
	e0Mvmts.push_back(e0_m1);

	Equation e0_eq2(3, -45, -100, 0.07f, 0.001f, MIN, 100, true, fhd);
	Movement e0_m2(1285, fhd);
	e0_m2.push_back(e0_eq2);
	e0Mvmts.push_back(e0_m2);

	Equation e0_eq3(0, 0, -100, 0, 0, MIN, 100, true, fhd);
	Movement e0_m3(1285, fhd);
	e0_m3.push_back(e0_eq3);
	e0Mvmts.push_back(e0_m3);


	
	Equation e1_eq0(2, -60, -700, 0.25f, 1, MAX, 60, false, fhd);
	Movement e1_m0(134, fhd);
	e1_m0.push_back(e1_eq0);
	e1Mvmts.push_back(e1_m0);

	Equation e1_eq1(2, -110, -700, 0.25f, 1, MAX, 60, false, fhd);
	Movement e1_m1(334, fhd);
	e1_m1.push_back(e1_eq1);
	e1Mvmts.push_back(e1_m1);

	Equation e1_eq2(2, -160, -700, 0.25f, 1, MAX, 60, false, fhd);
	Movement e1_m2(534, fhd);
	e1_m2.push_back(e1_eq2);
	e1Mvmts.push_back(e1_m2);

	Equation e1_eq3(2, -210, -700, 0.25f, 1, MAX, 60, false, fhd);
	Movement e1_m3(734, fhd);
	e1_m3.push_back(e1_eq3);
	e1Mvmts.push_back(e1_m3);

	Equation e1_eq4(2, -260, -700, 0.25f, 1, MAX, 60, false, fhd);
	Movement e1_m4(934, fhd);
	e1_m4.push_back(e1_eq4);
	e1Mvmts.push_back(e1_m4);



	Equation eBoss_eq0(0, 0, -100, 0, 0, 70, 80, true, fhd);
	Equation eBoss_eq1(0, 0, -100, 0, 0, 1250, 80, false, fhd);
	Equation eBoss_eq3(0, 0, -100, 0, 0, MIN, 80, true, fhd);
	Movement eBoss_m0(1340, fhd);
	for (int i = 0; i < 9; i++) {
		eBoss_m0.push_back(eBoss_eq0);
		eBoss_m0.push_back(eBoss_eq1);
	}
	eBoss_m0.push_back(eBoss_eq3);
	eBossMvmts.push_back(eBoss_m0);
}