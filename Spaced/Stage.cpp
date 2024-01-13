#include "Stage.h"


Stage::Stage(std::map<std::string, sf::Texture>& textures) {
	this->textures = textures;
	stage_num = 1;
	 
	int s1flags_size = sizeof(eflags);
	for (int i = 0; i < s1flags_size; i++) {
		eflags[i] = false;
	}
	boss_flag = false;
}


void Stage::spawn(std::vector<GameEntity*>* entities) {
	int rand; //RNG number
	float time = std::round(10 * clock.getElapsedTime().asSeconds()) / 10; //round to tenths
	float boss_time = std::round(10 * boss_clock.getElapsedTime().asSeconds()) / 10; //round to tenths
	
	if (boss_flag == false && boss_time == 1) {
		rand = std::rand() % enemyEqs.eBossEqs_size;
		GameEntity* eBoss = new EnemyBoss(textures["enemyBoss"], enemyEqs.eBossEqs_startPos[rand]);
		eBoss->setEqs(enemyEqs.eBossEqs[rand]);
		entities->push_back(eBoss);
		boss_flag = true;
	}
	else if (boss_time == 231) {
		boss_flag = false;
		boss_clock.restart();
	}

	switch (stage_num) {
	case 1: 
		if (eflags[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			GameEntity* e0 = new Enemy0(textures["enemy0"], enemyEqs.e0Eqs_startPos[rand]);
			e0->setEqs(enemyEqs.e0Eqs[rand]);
			entities->push_back(e0);

			eflags[0] = true;
		}
		else if (eflags[1] == false && time == 3) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			GameEntity* e0 = new Enemy0(textures["enemy0"], enemyEqs.e0Eqs_startPos[rand]);
			e0->setEqs(enemyEqs.e0Eqs[rand]);
			entities->push_back(e0);

			GameEntity* e1 = new Enemy1(textures["enemy1"], enemyEqs.e1Eqs_startPos[0]);
			e1->setEqs(enemyEqs.e1Eqs[0]);
			entities->push_back(e1);

			eflags[1] = true;
		}
		else if (eflags[2] == false && time == 4.5f) {
			GameEntity* e1 = new Enemy1(textures["enemy1"], enemyEqs.e1Eqs_startPos[1]);
			e1->setEqs(enemyEqs.e1Eqs[1]);
			entities->push_back(e1);

			eflags[2] = true;
		}
		else if (eflags[3] == false && time == 6) {
			GameEntity* e1 = new Enemy1(textures["enemy1"], enemyEqs.e1Eqs_startPos[2]);
			e1->setEqs(enemyEqs.e1Eqs[2]);
			entities->push_back(e1);

			eflags[3] = true;
		}
		else if (eflags[4] == false && time == 7.5f) {
			GameEntity* e1 = new Enemy1(textures["enemy1"], enemyEqs.e1Eqs_startPos[3]);
			e1->setEqs(enemyEqs.e1Eqs[3]);
			entities->push_back(e1);
			eflags[4] = true;
		}
		else if (eflags[5] == false && time == 9) {
			GameEntity* e1 = new Enemy1(textures["enemy1"], enemyEqs.e1Eqs_startPos[4]);
			e1->setEqs(enemyEqs.e1Eqs[4]);
			entities->push_back(e1);
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
	/*
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
		*/
	}
}


EnemyEqs::EnemyEqs() {
	MIN = -1000;
	MAX = 10000;

	//pt, xt, yt, m_xt, m_yt, x_max, speed_mult, reverse,
	std::vector<Equation> eqs;
	eqs.push_back(Equation(2, -150, -250, 0.25f, 0.005f, MAX, 1, false));
	e0Eqs.push_back(eqs);
	e0Eqs_startPos.push_back(-5);

	eqs.clear();
	eqs.push_back(Equation(3, 67, -300, -0.07f, 0.001f, MAX, 1, false));
	e0Eqs.push_back(eqs);
	e0Eqs_startPos.push_back(-5);

	eqs.clear();
	eqs.push_back(Equation(3, -45, -100, 0.07f, 0.001f, MIN, 1, true));
	e0Eqs.push_back(eqs);
	e0Eqs_startPos.push_back(1285);

	eqs.clear();
	eqs.push_back(Equation(0, 0, -100, 0, 0, MIN, 1, true));
	e0Eqs.push_back(eqs);
	e0Eqs_startPos.push_back(1285);

	e0Eqs_size = e0Eqs.size();
	
	//E1: x^2 wave (0-6)
	eqs.clear();
	eqs.push_back(Equation(2, -60, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(135);

	eqs.clear();
	eqs.push_back(Equation(2, -110, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(335);

	eqs.clear();
	eqs.push_back(Equation(2, -160, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(535);

	eqs.clear();
	eqs.push_back(Equation(2, -210, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(735);

	eqs.clear();
	eqs.push_back(Equation(2, -260, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(935);

	eqs.clear();
	eqs.push_back(Equation(2, -310, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1135);

	eqs.clear();
	eqs.push_back(Equation(2, -10, -700, 0.25f, 1, MAX, 60 * 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(-2);


	//E1: vertical line (7-19)
	eqs.clear();
	eqs.push_back(Equation(1, -100, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(100);

	eqs.clear();
	eqs.push_back(Equation(1, -200, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(200);

	eqs.clear();
	eqs.push_back(Equation(1, -300, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(300);

	eqs.clear();
	eqs.push_back(Equation(1, -400, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(400);

	eqs.clear();
	eqs.push_back(Equation(1, -500, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(500);

	eqs.clear();
	eqs.push_back(Equation(1, -600, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(600);

	eqs.clear();
	eqs.push_back(Equation(1, -700, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(700);

	eqs.clear();
	eqs.push_back(Equation(1, -800, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(800);

	eqs.clear();
	eqs.push_back(Equation(1, -900, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(900);

	eqs.clear();
	eqs.push_back(Equation(1, -1000, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1000);

	eqs.clear();
	eqs.push_back(Equation(1, -1100, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1100);

	eqs.clear();
	eqs.push_back(Equation(1, -1200, 0, 1, 99, MIN, 1, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1200);

	e1Eqs_size = e1Eqs.size();

	//EBoss: right side
	eqs.clear();
	for (int i = 0; i < 9; i++) {
		eqs.push_back(Equation(0, 0, -125, 0, 0, 95, 1, true));
		eqs.push_back(Equation(0, 0, -125, 0, 0, 1186, 1, false));
	}
	eqs.push_back(Equation(0, 0, -125, 0, 0, MIN, 1, true));
	eBossEqs.push_back(eqs);
	eBossEqs_startPos.push_back(1360);

	//EBoss: left side
	eqs.clear();
	for (int i = 0; i < 9; i++) {
		eqs.push_back(Equation(0, 0, -125, 0, 0, 1185, 1, false));
		eqs.push_back(Equation(0, 0, -125, 0, 0, 95, 1, true));
	}
	eqs.push_back(Equation(0, 0, -125, 0, 0, MAX, 1, false));
	eBossEqs.push_back(eqs);
	eBossEqs_startPos.push_back(-80);

	eBossEqs_size = eBossEqs.size();
}