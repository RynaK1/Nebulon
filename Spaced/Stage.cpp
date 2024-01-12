#include "Stage.h"

/*
Stage::Stage(std::map<std::string, sf::Texture>* textures, bool fhd) {
	this->fhd = fhd;
	this->textures = *textures;

	int s1flags_size = sizeof(eflags);
	for (int i = 0; i < s1flags_size; i++) {
		eflags[i] = false;
	}
	boss_flag = false;
}


void Stage::spawn(int stage, LiveEntities* live_entities) {
	float time = std::round(10 * clock.getElapsedTime().asSeconds()) / 10; //round to tenths
	float boss_time = std::round(10 * boss_clock.getElapsedTime().asSeconds()) / 10; //round to tenths
	if (boss_flag == false && boss_time == 1) {
		enemies["eBoss"].setEqs(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()]);
		live_entities->spawn(enemies["eBoss"]);
		boss_flag = true;
	}
	else if (boss_time == 231) {
		boss_flag = false;
		boss_clock.restart();
	}
	switch (stage) {
		/*
	case 1: 
		if (eflags[0] == false && time == 1) {
			enemies["e0"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 3) {
			enemies["e0"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			enemies["e1"].setEqs(enemyEqs.e1Eqs[0]);
			spawned.push_back(enemies["e1"]);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.5f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[1]);
			spawned.push_back(enemies["e1"]);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 6) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[2]);
			spawned.push_back(enemies["e1"]);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 7.5f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[3]);
			spawned.push_back(enemies["e1"]);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 9) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[4]);
			spawned.push_back(enemies["e1"]);
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
			enemies["eBoss"].setEqs(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()]);
			spawned.push_back(enemies["eBoss"]);
			boss_flag = true;
		}
		else if (boss_time == 219.5f) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			enemies["e0"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 3) {
			enemies["e0"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			enemies["e1"].setEqs(enemyEqs.e1Eqs[0]);
			spawned.push_back(enemies["e1"]);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.4f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[1]);
			spawned.push_back(enemies["e1"]);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 5.8f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[2]);
			spawned.push_back(enemies["e1"]);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 7.2f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[3]);
			spawned.push_back(enemies["e1"]);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 8.6f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[4]);
			spawned.push_back(enemies["e1"]);
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
			enemies["e0"].setEqs(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()]);
			spawned.push_back(enemies["e0"]);
			boss_flag = true;
		}
		else if (boss_time == 208) {
			boss_flag = false;
			boss_clock.restart();
		}
		if (eflags[0] == false && time == 1) {
			enemies["e0"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			eflags[0] = true;
		}
		else if (eflags[6] == false && time == 2) {
			enemies["e1"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			eflags[6] = true;
		}
		else if (eflags[1] == false && time == 3) {
			enemies["e0"].setEqs(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()]);
			spawned.push_back(enemies["e0"]);
			enemies["e1"].setEqs(enemyEqs.e1Eqs[0]);
			spawned.push_back(enemies["e1"]);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.3f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[1]);
			spawned.push_back(enemies["e1"]);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 5.6f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[2]);
			spawned.push_back(enemies["e1"]);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 6.9f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[3]);
			spawned.push_back(enemies["e1"]);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 8.2f) {
			enemies["e1"].setEqs(enemyEqs.e1Eqs[4]);
			spawned.push_back(enemies["e1"]);
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
	/*
	case 4:
		if (boss_flag == false && boss_time == 1) {
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 196.4f) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[6] == false && time == 2) {
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			eflags[6] = true;
		}
		else if (eflags[1] == false && time == 3) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.2f) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 5.4f) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 6.6f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 7.8f) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
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
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 185) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[5], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.6f) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.7f) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4.8f) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 5.9f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[6] == false && time == 7) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 8.1f) {
			Enemy1* e1_5 = new Enemy1(enemyEqs.e1Eqs[6], textures["enemy1"], fhd);
			spawned.push_back(e1_5);
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
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 173) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[5], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.5f) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.5f) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4.5f) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 5.5f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[6] == false && time == 6.5f) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 7.5f) {
			Enemy1* e1_5 = new Enemy1(enemyEqs.e1Eqs[6], textures["enemy1"], fhd);
			spawned.push_back(e1_5);
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
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 162) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[9] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_7);
			eflags[9] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[5], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.9f) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.8f) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4.7f) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 5.6f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[6] == false && time == 6.5f) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 7.4f) {
			Enemy1* e1_5 = new Enemy1(enemyEqs.e1Eqs[6], textures["enemy1"], fhd);
			spawned.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 8.3f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
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
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 150) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[11] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_7);
			eflags[11] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[5], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.4f) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3.2f) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 4) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 4.8f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[10] == false && time == 5.2f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
			eflags[10] = true;
		}
		else if (eflags[6] == false && time == 5.6f) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 6.4f) {
			Enemy1* e1_5 = new Enemy1(enemyEqs.e1Eqs[6], textures["enemy1"], fhd);
			spawned.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 7) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
			eflags[8] = true;
		}
		else if (eflags[9] == false && time == 7.8f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
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
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 138.5f) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[11] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_7);
			eflags[11] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[5], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.3f) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 3) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 3.7f) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 4.3f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[10] == false && time == 4.5f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
			eflags[10] = true;
		}
		else if (eflags[6] == false && time == 5) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time == 5.7f) {
			Enemy1* e1_5 = new Enemy1(enemyEqs.e1Eqs[6], textures["enemy1"], fhd);
			spawned.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 6.3f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
			eflags[8] = true;
		}
		else if (eflags[9] == false && time == 7) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
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
			EnemyBoss* eBoss_0 = new EnemyBoss(enemyEqs.eBossEqs[std::rand() % enemyEqs.eBossEqs.size()], textures["enemyBoss"], fhd);
			spawned.push_back(eBoss_0);
			boss_flag = true;
		}
		else if (boss_time == 127) {
			boss_flag = false;
			boss_clock.restart();
		}

		if (eflags[0] == false && time == 1) {
			Enemy0* e0_0 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_0);
			eflags[0] = true;
		}
		else if (eflags[11] == false && time == 1.5f) {
			Enemy1* e1_7 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_7);
			eflags[11] = true;
		}
		else if (eflags[1] == false && time == 2) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy0* e0_2 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_2);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[5], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 2.3f) {
			Enemy0* e0_1 = new Enemy0(enemyEqs.e0Eqs[std::rand() % enemyEqs.e0Eqs.size()], textures["enemy0"], fhd);
			spawned.push_back(e0_1);
			Enemy1* e1_0 = new Enemy1(enemyEqs.e1Eqs[0], textures["enemy1"], fhd);
			spawned.push_back(e1_0);
			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 2.8f) {
			Enemy1* e1_1 = new Enemy1(enemyEqs.e1Eqs[1], textures["enemy1"], fhd);
			spawned.push_back(e1_1);
			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 3.3f) {
			Enemy1* e1_2 = new Enemy1(enemyEqs.e1Eqs[2], textures["enemy1"], fhd);
			spawned.push_back(e1_2);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 3.8f) {
			Enemy1* e1_3 = new Enemy1(enemyEqs.e1Eqs[3], textures["enemy1"], fhd);
			spawned.push_back(e1_3);
			eflags[5] = true;
		}
		else if (eflags[10] == false && time == 4) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
			eflags[10] = true;
		}
		else if (eflags[6] == false && time == 4.3f) {
			Enemy1* e1_4 = new Enemy1(enemyEqs.e1Eqs[4], textures["enemy1"], fhd);
			spawned.push_back(e1_4);
			eflags[6] = true;
		}
		else if (eflags[7] == false && time ==  4.8f) {
			Enemy1* e1_5 = new Enemy1(enemyEqs.e1Eqs[6], textures["enemy1"], fhd);
			spawned.push_back(e1_5);
			eflags[7] = true;
		}
		else if (eflags[8] == false && time == 5.3f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
			eflags[8] = true;
		}
		else if (eflags[9] == false && time == 5.8f) {
			Enemy1* e1_6 = new Enemy1(enemyEqs.e1Eqs[(std::rand() % 12) + 7], textures["enemy1"], fhd);
			spawned.push_back(e1_6);
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
	
}


EnemyEqs::EnemyEqs(float speed_up) {
	MIN = -1000;
	MAX = 10000;

	//pt, xt, yt, m_xt, m_yt, x_max, speed_mult, reverse,
	std::vector<Equation> eqs;
	eqs.push_back(Equation(2, -150, -250, 0.25f, 0.005f, MAX, 100 * speed_up, false));
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(3, 67, -300, -0.07f, 0.001f, MAX, 100 * speed_up, false));
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(3, -45, -100, 0.07f, 0.001f, MIN, 100 * speed_up, true)); //1285
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(0, 0, -100, 0, 0, MIN, 100 * speed_up, true)); //1285
	e0Eqs.push_back(eqs);


	
	//E1: x^2 wave (0-6)
	eqs.clear();
	eqs.push_back(Equation(2, -60, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //134
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(2, -110, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //334
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(2, -160, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //534
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(2, -210, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //734
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(2, -260, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //934
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(2, -10, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //-2
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(2, -310, -700, 0.25f, 1, MAX, 60 * speed_up, false)); //1134
	e0Eqs.push_back(eqs);

	//E1: vertical line (7-19)
	eqs.clear();
	eqs.push_back(Equation(1, -100, 0, 1, 99, MIN, 7 * speed_up, true)); //100
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -200, 0, 1, 99, MIN, 7 * speed_up, true)); //200
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -300, 0, 1, 99, MIN, 7 * speed_up, true)); //300
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -400, 0, 1, 99, MIN, 7 * speed_up, true)); //400
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -500, 0, 1, 99, MIN, 7 * speed_up, true)); //500
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -600, 0, 1, 99, MIN, 7 * speed_up, true)); //600
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -700, 0, 1, 99, MIN, 7 * speed_up, true)); //700
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -800, 0, 1, 99, MIN, 7 * speed_up, true)); //800
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -900, 0, 1, 99, MIN, 7 * speed_up, true)); //900
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -1000, 0, 1, 99, MIN, 7 * speed_up, true)); //1000
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -1100, 0, 1, 99, MIN, 7 * speed_up, true)); //1100
	e0Eqs.push_back(eqs);

	eqs.clear();
	eqs.push_back(Equation(1, -1200, 0, 1, 99, MIN, 7 * speed_up, true)); //1200
	e0Eqs.push_back(eqs);

	//EBoss: right side
	eqs.clear();
	for (int i = 0; i < 9; i++) {
		eqs.push_back(Equation(0, 0, -100, 0, 0, 70, 5 * speed_up, true)); //1340
		eqs.push_back(Equation(0, 0, -100, 0, 0, 1160, 5 * speed_up, false));
	}
	eqs.push_back(Equation(0, 0, -100, 0, 0, MIN, 5 * speed_up, true));
	eBossEqs.push_back(eqs);

	//EBoss: left side
	eqs.clear();
	for (int i = 0; i < 9; i++) {
		eqs.push_back(Equation(0, 0, -100, 0, 0, 1160, 5 * speed_up, false)); //-60
		eqs.push_back(Equation(0, 0, -100, 0, 0, 70, 5 * speed_up, true));
	}
	eqs.push_back(Equation(0, 0, -100, 0, 0, MAX, 80 * speed_up, false));
	eBossEqs.push_back(eqs);
}
*/