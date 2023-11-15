#include "Stage.h"

Stage::Stage(std::map<std::string, sf::Texture>* textures, bool fhd) {
	this->fhd = fhd;
	this->textures = *textures;

	int s1flags_size = sizeof(eflags);
	for (int i = 0; i < s1flags_size; i++) {
		eflags[i] = false;
	}
	boss_flag = false;
}


std::vector<Enemy*> Stage::spawn(int stage) {
	std::vector<Enemy*> spwn;
	float time = std::round(10 * clock.getElapsedTime().asSeconds()) / 10.0f;
	float boss_time = std::round(10 * boss_clock.getElapsedTime().asSeconds()) / 10.0f;
	/*
	Creating stage
		- Create proper sized flag arr equating to the number of spawning instances within a cycle
		- Create if statement for appropriate timing
		- Create enemy with appropriate or randomized movement and texture
		- Push back created enemy to spwn
	*/
	if (boss_flag == false && boss_time == 1) {
		EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
		spwn.push_back(eBoss_0);
		boss_flag = true;
	}
	else if (boss_time == 231) {
		boss_flag = false;
		boss_clock.restart();
	}
	switch (stage) {
	case 1: 
		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 3) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.5f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 6) {
			Enemy1* e1_2 =  new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 7.5f) {
			Enemy1*  e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 9) {
			Enemy1* e1_4 =  new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[5] = true;
		}
		else if (time == 10) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 2:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 219.5f) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 3) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.4f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 5.8f) {
			Enemy1* e1_2 =  new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 7.2f) {
			Enemy1*  e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 8.6f) {
			Enemy1* e1_4 =  new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[5] = true;
		}
		else if (time == 9.5f) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 3:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 208) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[6] == false && time == 2) {
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			eflags[6] = true;
		}
		else if (eflags[1] == false && time == 3) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.3f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 5.6f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 6.9f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 8.2f) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[5] = true;
		}
		else if (time == 9) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 4:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 196.4f) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[6] == false && time == 2) {
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			eflags[6] = true;
		}
		else if (eflags[1] == false && time == 3) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.2f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 5.4f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 6.6f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 7.8f) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[5] = true;
		}
		else if (time == 8.5f) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 5:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 185) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[5], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.6f) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.7f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4.8f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 5.9f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[6] == false && time == 7) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 8.1f) {
			Enemy1* e1_5 = new Enemy1(enemyMvmt.e1Mvmts[6], textures["enemy1"], fhd);
			spwn.push_back(e1_5);
			eflags[7] = true;
		}
		else if (time == 8.5f) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 6:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 173) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[5], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.5f) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.5f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4.5f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 5.5f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[6] == false && time == 6.5f) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 7.5f) {
			Enemy1* e1_5 = new Enemy1(enemyMvmt.e1Mvmts[6], textures["enemy1"], fhd);
			spwn.push_back(e1_5);
			eflags[7] = true;
		}
		else if (time == 8) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 7:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 162) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[9] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_7);
			eflags[9] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[5], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.9f) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.8f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4.7f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 5.6f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[6] == false && time == 6.5f) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 7.4f) {
			Enemy1* e1_5 = new Enemy1(enemyMvmt.e1Mvmts[6], textures["enemy1"], fhd);
			spwn.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 8.3f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[8] = true;
		}
		else if (time == 9) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 8:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 150) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[11] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_7);
			eflags[11] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[5], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.4f) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.2f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 4.8f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[10] == false && time == 5.2f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[10] = true;
		}
		else if (eflags[6] == false && time == 5.6f) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 6.4f) {
			Enemy1* e1_5 = new Enemy1(enemyMvmt.e1Mvmts[6], textures["enemy1"], fhd);
			spwn.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 7) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[8] = true;
		}
		else if (eflags[9] == false && time == 7.8f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[9] = true;
		}
		else if (time == 8) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 9:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 138.5f) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[11] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_7);
			eflags[11] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[5], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.3f) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 3.7f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 4.3f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[10] == false && time == 4.5f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[10] = true;
		}
		else if (eflags[6] == false && time == 5) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 5.7f) {
			Enemy1* e1_5 = new Enemy1(enemyMvmt.e1Mvmts[6], textures["enemy1"], fhd);
			spwn.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 6.3f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[8] = true;
		}
		else if (eflags[9] == false && time == 7) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[9] = true;
		}
		else if (time == 7.5f) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
		break;
	case 10:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyMvmt.eBossMvmts[std::rand() % enemyMvmt.eBossMvmts.size()], textures["enemyBoss"], fhd);
			spwn.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 127) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[11] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_7);
			eflags[11] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[5], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.3f) {
			Enemy0* e0_1 = new Enemy0(enemyMvmt.e0Mvmts[std::rand() % enemyMvmt.e0Mvmts.size()], textures["enemy0"], fhd);
			spwn.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyMvmt.e1Mvmts[0], textures["enemy1"], fhd);
			spwn.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 2.8f) {
			Enemy1* e1_1 = new Enemy1(enemyMvmt.e1Mvmts[1], textures["enemy1"], fhd);
			spwn.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 3.3f) {
			Enemy1* e1_2 = new Enemy1(enemyMvmt.e1Mvmts[2], textures["enemy1"], fhd);
			spwn.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 3.8f) {
			Enemy1* e1_3 = new Enemy1(enemyMvmt.e1Mvmts[3], textures["enemy1"], fhd);
			spwn.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[10] == false && time == 4) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[10] = true;
		}
		else if (eflags[6] == false && time == 4.3f) {
			Enemy1* e1_4 = new Enemy1(enemyMvmt.e1Mvmts[4], textures["enemy1"], fhd);
			spwn.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time ==  4.8f) {
			Enemy1* e1_5 = new Enemy1(enemyMvmt.e1Mvmts[6], textures["enemy1"], fhd);
			spwn.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 5.3f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[8] = true;
		}
		else if (eflags[9] == false && time == 5.8f) {
			Enemy1* e1_6 = new Enemy1(enemyMvmt.e1Mvmts[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spwn.push_back(e1_6);
			eflags[9] = true;
		}
		else if (time == 6) {
			int eflags_size = sizeof(eflags);
			for (int i = 0; i < eflags_size; i++) {
				eflags[i] = false;
			}
			clock.restart();
		}
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

EnemyMvmt::EnemyMvmt(float speed, bool fhd) {
	MIN = -1000;
	MAX = 10000;

	//pt, xt, yt, m_xt, m_yt, x_max, speed, reverse, fhd
	Equation e0_eq0(2, -150, -250, 0.25f, 0.005f, MAX, 100 * (1 + speed), false, fhd);
	Movement e0_m0(-15, fhd);
	e0_m0.push_back(e0_eq0);
	e0Mvmts.push_back(e0_m0);

	Equation e0_eq1(3, 67, -300, -0.07f, 0.001f, MAX, 100 * (1 + speed), false, fhd);
	Movement e0_m1(-15, fhd);
	e0_m1.push_back(e0_eq1);
	e0Mvmts.push_back(e0_m1);

	Equation e0_eq2(3, -45, -100, 0.07f, 0.001f, MIN, 100 * (1 + speed), true, fhd);
	Movement e0_m2(1285, fhd);
	e0_m2.push_back(e0_eq2);
	e0Mvmts.push_back(e0_m2);

	Equation e0_eq3(0, 0, -100, 0, 0, MIN, 100 * (1 + speed), true, fhd);
	Movement e0_m3(1285, fhd);
	e0_m3.push_back(e0_eq3);
	e0Mvmts.push_back(e0_m3);


	
	//E1: x^2 wave
	Equation e1_eq0(2, -60, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m0(134, fhd);  //0
	e1_m0.push_back(e1_eq0);
	e1Mvmts.push_back(e1_m0);

	Equation e1_eq1(2, -110, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m1(334, fhd); //1
	e1_m1.push_back(e1_eq1);
	e1Mvmts.push_back(e1_m1);

	Equation e1_eq2(2, -160, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m2(534, fhd);  //2
	e1_m2.push_back(e1_eq2);
	e1Mvmts.push_back(e1_m2);

	Equation e1_eq3(2, -210, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m3(734, fhd); //3
	e1_m3.push_back(e1_eq3);
	e1Mvmts.push_back(e1_m3);

	Equation e1_eq4(2, -260, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m4(934, fhd);  //4
	e1_m4.push_back(e1_eq4);
	e1Mvmts.push_back(e1_m4);

	Equation e1_eq5(2, -10, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m5(-2, fhd); //5
	e1_m5.push_back(e1_eq5);
	e1Mvmts.push_back(e1_m5);

	Equation e1_eq6(2, -310, -700, 0.25f, 1, MAX, 60 * (1 + speed), false, fhd);
	Movement e1_m6(1134, fhd); //6
	e1_m6.push_back(e1_eq6);
	e1Mvmts.push_back(e1_m6);

	//E1: vertical line
	Equation e1_eq7(1, -100, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m7(100, fhd); //7
	e1_m7.push_back(e1_eq7);
	e1Mvmts.push_back(e1_m7);

	Equation e1_eq8(1, -200, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m8(200, fhd); //8
	e1_m8.push_back(e1_eq8);
	e1Mvmts.push_back(e1_m8);

	Equation e1_eq9(1, -300, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m9(300, fhd); //9
	e1_m9.push_back(e1_eq9);
	e1Mvmts.push_back(e1_m9);

	Equation e1_eq10(1, -400, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m10(400, fhd); //10
	e1_m10.push_back(e1_eq10);
	e1Mvmts.push_back(e1_m10);

	Equation e1_eq11(1, -500, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m11(500, fhd); //11
	e1_m11.push_back(e1_eq11);
	e1Mvmts.push_back(e1_m11);

	Equation e1_eq12(1, -600, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m12(600, fhd); //12
	e1_m12.push_back(e1_eq12);
	e1Mvmts.push_back(e1_m12);

	Equation e1_eq13(1, -700, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m13(700, fhd); //13
	e1_m13.push_back(e1_eq13);
	e1Mvmts.push_back(e1_m13);

	Equation e1_eq14(1, -800, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m14(800, fhd); //14
	e1_m14.push_back(e1_eq14);
	e1Mvmts.push_back(e1_m14);

	Equation e1_eq15(1, -900, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m15(900, fhd); //15
	e1_m15.push_back(e1_eq15);
	e1Mvmts.push_back(e1_m15);

	Equation e1_eq16(1, -1000, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m16(1000, fhd); //16
	e1_m16.push_back(e1_eq16);
	e1Mvmts.push_back(e1_m16);

	Equation e1_eq17(1, -1100, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m17(1100, fhd); //17
	e1_m17.push_back(e1_eq17);
	e1Mvmts.push_back(e1_m17);

	Equation e1_eq18(1, -1200, 0, 1, 99, MIN, 7 * (1 + speed), true, fhd);
	Movement e1_m18(1200, fhd); //18
	e1_m18.push_back(e1_eq18);
	e1Mvmts.push_back(e1_m18);

	//EBoss: right side
	Equation eBoss_eq0(0, 0, -100, 0, 0, 70, 80 * (1 + speed), true, fhd);
	Equation eBoss_eq1(0, 0, -100, 0, 0, 1160, 80 * (1 + speed), false, fhd);
	Equation eBoss_eq3(0, 0, -100, 0, 0, MIN, 80 * (1 + speed), true, fhd);
	Movement eBoss_m0(1340, fhd);
	for (int i = 0; i < 9; i++) {
		eBoss_m0.push_back(eBoss_eq0);
		eBoss_m0.push_back(eBoss_eq1);
	}
	eBoss_m0.push_back(eBoss_eq3);
	eBossMvmts.push_back(eBoss_m0);

	//Eboss: left side
	Equation eBoss_eq4(0, 0, -100, 0, 0, MAX, 80 * (1 + speed), false, fhd);
	Movement eBoss_m1(-60, fhd);
	for (int i = 0; i < 9; i++) {
		eBoss_m1.push_back(eBoss_eq1);
		eBoss_m1.push_back(eBoss_eq0);
	}
	eBoss_m1.push_back(eBoss_eq4);
	eBossMvmts.push_back(eBoss_m1);
}


void Stage::reset() {
	clock.restart();
	boss_clock.restart();
	boss_flag = false;

	size_t eflags_size = sizeof(eflags);
	for (int i = 0; i < eflags_size; i++) {
		eflags[i] = false;
	}
}


void Stage::load(int stage) {
	enemyMvmt = EnemyMvmt((float)(((stage - 1) % 10) * 0.1f), fhd);
}