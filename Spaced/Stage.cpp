#include "Stage.h"


EnemyFactory::EnemyFactory(std::map<std::string, sf::Texture>& textures) {
	this->textures = textures;
}

Enemy* EnemyFactory::create(int type, float start_pos, int stage_num) {
	Enemy* enemy = nullptr;
	float speed;
	stage_num -= 1;
	switch (type) {
	case 0:
		speed = 125 + 125 * 0.05f * (stage_num % 10);
		enemy = new Enemy(textures["enemy0"], start_pos, speed, 15, 0, 20, false);
		enemy->setScale(0.25f, 0.25f);
		break;
	case 1:
		speed = 125 + 125 * 0.05f * (stage_num % 10);
		enemy = new Enemy(textures["enemy1"], start_pos, speed, 20, 1, 20, false);
		enemy->setScale(0.16f, 0.16f);
		enemy->setRotation(180);
		break;
	case 100:
		speed = 100 + 100 * 0.05f * (stage_num % 10);
		enemy = new Enemy(textures["enemy100"], start_pos, speed, 100, 100, 34, true);
		enemy->setScale(0.7f, 0.7f);
		break;
	}

	return enemy;
}



Stage::Stage(std::map<std::string, sf::Texture>& textures) {
	enemyFactory = EnemyFactory(textures);
	this->textures = textures;
	boss_spawned = false;
	stage_num = 0;
	 
	int s1flags_size = sizeof(enemy_spawned);
	for (int i = 0; i < s1flags_size; i++) {
		enemy_spawned[i] = false;
	}
}

int Stage::getStage_num() {
	return stage_num;
}

bool Stage::getBoss_spawned() {
	return boss_spawned;
}

void Stage::setBoss_spawned(bool boss_spawned) {
	this->boss_spawned = boss_spawned;
}

void Stage::nextStage() {
	stage_num += 1;
	boss_spawned = false;	
	int eflags_size = sizeof(enemy_spawned);
	for (int i = 0; i < eflags_size; i++) {
		enemy_spawned[i] = false;
	}
	boss_clock.restart();
	clock.restart();
}

void Stage::spawn(std::vector<Enemy*>* enemies) {
	int rand; //RNG number
	float time = std::round(10 * clock.getElapsedTime().asSeconds()) / 10; //round to tenths
	float boss_time = std::round(10 * boss_clock.getElapsedTime().asSeconds()) / 10; //round to tenths

	size_t before_size = enemies->size();

	switch (stage_num) {
	case 1: 
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 231) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[1] == false && time == 3) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 4.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 6) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 7.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);
			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 9) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);
			enemy_spawned[5] = true;
		}
		else if (time == 10) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 2:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 219.5f) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[1] == false && time == 3) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 4.4f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 5.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 7.2f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 8.6f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (time == 9.5f) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 3:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 208) {
			boss_spawned = false;
			boss_clock.restart();
		}
		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[6] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[1] == false && time == 3) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 4.3f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 5.6f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 6.9f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 8.2f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (time == 9) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 4:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 196.4f) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[6] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[1] == false && time == 3) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 4.2f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 5.4f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 6.6f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 7.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (time == 8.5f) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 5:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 185) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[1] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			rand = std::rand() % enemyEqs.e0Eqs_size;
			enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[5], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[5]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 2.6f) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 3.7f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 4.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 5.9f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (enemy_spawned[6] == false && time == 7) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[7] == false && time == 8.1f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[6], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[6]);
			enemies->push_back(enemy);
			enemy_spawned[7] = true;
		}
		else if (time == 8.5f) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 6:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 173) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[1] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			rand = std::rand() % enemyEqs.e0Eqs_size;
			enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[5], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[5]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 2.5f) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 3.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 4.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 5.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (enemy_spawned[6] == false && time == 6.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[7] == false && time == 7.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[6], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[6]);
			enemies->push_back(enemy);

			enemy_spawned[7] = true;
		}
		else if (time == 8) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 7:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 162) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[9] == false && time == 1.5f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[9] = true;
		}
		else if (enemy_spawned[1] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			rand = std::rand() % enemyEqs.e0Eqs_size;
			enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[5], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[5]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 2.9f) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 3.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 4.7f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 5.6f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (enemy_spawned[6] == false && time == 6.5f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[7] == false && time == 7.4f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[6], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[6]);
			enemies->push_back(enemy);

			enemy_spawned[7] = true;
		}
		else if (enemy_spawned[8] == false && time == 8.3f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[8] = true;
		}
		else if (time == 9) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 8:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 150) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[11] == false && time == 1.5f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[11] = true;
		}
		else if (enemy_spawned[1] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			rand = std::rand() % enemyEqs.e0Eqs_size;
			enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[5], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[5]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 2.4f) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 3.2f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 4) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 4.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (enemy_spawned[10] == false && time == 5.2f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[10] = true;
		}
		else if (enemy_spawned[6] == false && time == 5.6f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[7] == false && time == 6.4f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[6], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[6]);
			enemies->push_back(enemy);

			enemy_spawned[7] = true;
		}
		else if (enemy_spawned[8] == false && time == 7) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[8] = true;
		}
		else if (enemy_spawned[9] == false && time == 7.8f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[9] = true;
		}
		else if (time == 8) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 9:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 138.5f) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[11] == false && time == 1.5f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[11] = true;
		}
		else if (enemy_spawned[1] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			rand = std::rand() % enemyEqs.e0Eqs_size;
			enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[5], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[5]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 2.3f) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 3) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 3.7f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 4.3f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (enemy_spawned[10] == false && time == 4.5f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[10] = true;
		}
		else if (enemy_spawned[6] == false && time == 5) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[7] == false && time == 5.7f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[6], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[6]);
			enemies->push_back(enemy);

			enemy_spawned[7] = true;
		}
		else if (enemy_spawned[8] == false && time == 6.3f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[8] = true;
		}
		else if (enemy_spawned[9] == false && time == 7) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[9] = true;
		}
		else if (time == 7.5f) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
	case 10:
		if (boss_spawned == false && boss_time == 1) {
			rand = std::rand() % enemyEqs.eBossEqs_size;
			Enemy* enemy = enemyFactory.create(100, enemyEqs.eBossEqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.eBossEqs[rand]);
			enemies->push_back(enemy);

			boss_spawned = true;
		}
		else if (boss_time == 127) {
			boss_spawned = false;
			boss_clock.restart();
		}

		if (enemy_spawned[0] == false && time == 1) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[0] = true;
		}
		else if (enemy_spawned[11] == false && time == 1.5f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[11] = true;
		}
		else if (enemy_spawned[1] == false && time == 2) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			rand = std::rand() % enemyEqs.e0Eqs_size;
			enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[5], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[5]);
			enemies->push_back(enemy);

			enemy_spawned[1] = true;
		}
		else if (enemy_spawned[2] == false && time == 2.3f) {
			rand = std::rand() % enemyEqs.e0Eqs_size;
			Enemy* enemy = enemyFactory.create(0, enemyEqs.e0Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e0Eqs[rand]);
			enemies->push_back(enemy);

			enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[0], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[0]);
			enemies->push_back(enemy);

			enemy_spawned[2] = true;
		}
		else if (enemy_spawned[3] == false && time == 2.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[1], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[1]);
			enemies->push_back(enemy);

			enemy_spawned[3] = true;
		}
		else if (enemy_spawned[4] == false && time == 3.3f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[2], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[2]);
			enemies->push_back(enemy);

			enemy_spawned[4] = true;
		}
		else if (enemy_spawned[5] == false && time == 3.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[3], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[3]);
			enemies->push_back(enemy);

			enemy_spawned[5] = true;
		}
		else if (enemy_spawned[10] == false && time == 4) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[10] = true;
		}
		else if (enemy_spawned[6] == false && time == 4.3f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[4], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[4]);
			enemies->push_back(enemy);

			enemy_spawned[6] = true;
		}
		else if (enemy_spawned[7] == false && time ==  4.8f) {
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[6], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[6]);
			enemies->push_back(enemy);

			enemy_spawned[7] = true;
		}
		else if (enemy_spawned[8] == false && time == 5.3f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[8] = true;
		}
		else if (enemy_spawned[9] == false && time == 5.8f) {
			rand = (std::rand() % 12) + 7;
			Enemy* enemy = enemyFactory.create(1, enemyEqs.e1Eqs_startPos[rand], stage_num);
			enemy->setEqs(enemyEqs.e1Eqs[rand]);
			enemies->push_back(enemy);

			enemy_spawned[9] = true;
		}
		else if (time == 6) {
			int eflags_size = sizeof(enemy_spawned);
			for (int i = 0; i < eflags_size; i++) {
				enemy_spawned[i] = false;
			}
			clock.restart();
		}
		break;
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
	eqs.push_back(Equation(2, -10, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(-2);

	eqs.clear();
	eqs.push_back(Equation(2, -60, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(135);

	eqs.clear();
	eqs.push_back(Equation(2, -110, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(335);

	eqs.clear();
	eqs.push_back(Equation(2, -160, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(535);

	eqs.clear();
	eqs.push_back(Equation(2, -210, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(735);

	eqs.clear();
	eqs.push_back(Equation(2, -260, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(935);

	eqs.clear();
	eqs.push_back(Equation(2, -310, -700, 0.25f, 1, MAX, 1, false));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1135);

	//E1: vertical line (7-19)
	eqs.clear();
	eqs.push_back(Equation(1, -100, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(100);

	eqs.clear();
	eqs.push_back(Equation(1, -200, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(200);

	eqs.clear();
	eqs.push_back(Equation(1, -300, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(300);

	eqs.clear();
	eqs.push_back(Equation(1, -400, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(400);

	eqs.clear();
	eqs.push_back(Equation(1, -500, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(500);

	eqs.clear();
	eqs.push_back(Equation(1, -600, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(600);

	eqs.clear();
	eqs.push_back(Equation(1, -700, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(700);

	eqs.clear();
	eqs.push_back(Equation(1, -800, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(800);

	eqs.clear();
	eqs.push_back(Equation(1, -900, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(900);

	eqs.clear();
	eqs.push_back(Equation(1, -1000, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1000);

	eqs.clear();
	eqs.push_back(Equation(1, -1100, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1100);

	eqs.clear();
	eqs.push_back(Equation(1, -1200, 0, 1, 99, MIN, 0.1f, true));
	e1Eqs.push_back(eqs);
	e1Eqs_startPos.push_back(1200);

	e1Eqs_size = e1Eqs.size();

	//EBoss: right side
	eqs.clear();
	for (int i = 0; i < 9; i++) {
		eqs.push_back(Equation(0, 0, -125, 0, 0, 95, 1, true));
		eqs.push_back(Equation(0, 0, -125, 0, 0, 1185, 1, false));
	}
	eqs.push_back(Equation(0, 0, -125, 0, 0, MIN, 1, true));
	eBossEqs.push_back(eqs);
	eBossEqs_startPos.push_back(1345);

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