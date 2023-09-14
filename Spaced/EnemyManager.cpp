#include "EnemyManager.h"

EnemyManager::EnemyManager() {
    enemy_t1.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 48, 23, 28));
    enemy_t2.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(25, 48, 30, 29));
    enemy_boss.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 80, 182, 332));
    res = readFromFile("resolution");
    enemies_size = 0;
}


int EnemyManager::getEnemies_size() {
    return enemies_size;
}


std::vector<Enemy> EnemyManager::getEnemies() {
    return enemies;
}


void EnemyManager::spawn(int type, Equation mv) {
    Enemy enemy;
    if (type == 1) {
        enemy = EnemyT1(mv);
        enemy.getSprite().setTexture(enemy_t1);
    }
    else if (type == 2) {
        enemy = EnemyT2(mv);
        enemy.getSprite().setTexture(enemy_t2);
    }
    else {
        enemy = EnemyBoss(mv);
        enemy.getSprite().setTexture(enemy_boss);
    }

    float he = pow((mv.mult_horiz * mv.x) + mv.horiz, mv.pwr);
    float result = (he * mv.mult_vert) + mv.vert;
    enemy.getSprite().setPosition(mv.x, result);
    enemies.push_back(enemy);

    enemies_size += 1;
}


void EnemyManager::updateEnemies(float time) {
    int x_max = 1280;
    int y_max = 720;
    if (res.compare("1920x1080") == 0) {
        x_max = 1920;
        y_max = 1080;
    }

    for (int i = 0; i < enemies_size; i++) {
        Equation mv = enemies[i].getMvmt();
        enemies[i].setEqX(mv.x + 1);
        mv.x += 1;
        float he = pow((mv.mult_horiz * mv.x) + mv.horiz, mv.pwr);
        float result = (he * mv.mult_vert) + mv.vert;
        enemies[i].getSprite().setPosition(mv.x, -result);

        switch (enemies[i].getType()) {
        case 1:
            if (mv.x <= -23 || mv.x >= x_max + 23 ||
                result >= 28 || result <= -y_max - 28) {
                enemies.erase(enemies.begin() + i);
                i -= 1;
                enemies_size -= 1;
            }
            break;
        case 2:
            if (mv.x <= -30 || mv.x >= x_max + 30 ||
                result >= 29 || result <= -y_max - 29) {
                enemies.erase(enemies.begin() + i);
                i -= 1;
                enemies_size -= 1;
            }
            break;
        default:
            break;
        }
    }

    std::cout << enemies_size << std::endl;
}



void Enemy::setEqX(float x) {
    mvmt.x = x;
}


int Enemy::getType() {
    return type;
}


Equation Enemy::getMvmt() {
    return mvmt;
}


sf::Sprite& Enemy::getSprite() {
    return sprite;
}



void Enemy::attack() {}



EnemyT1::EnemyT1(Equation mv) {
    sprite.setOrigin(12, 14);
    type = 1;
    mvmt = mv;
}


void EnemyT1::attack() {

}



EnemyT2::EnemyT2(Equation mv) {
    sprite.setOrigin(15, 15);
    type = 2;
    mvmt = mv;
}


void EnemyT2::attack() {

}



EnemyBoss::EnemyBoss(Equation mv) {
    sprite.setOrigin(91, 166);
    type = 10;
    mvmt = mv;
}

void EnemyBoss::attack() {

}
