#include "EnemyManager.h"

Enemy::Enemy() {
    type = 0;
    mvmt.pt = 0;
    mvmt.xt = 0;
    mvmt. yt = 0;
    mvmt. m_xt = 0;
    mvmt. m_yt = 0;
}

void Enemy::setSprite(sf::Sprite sprite) {
    this->sprite = sprite;
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

    float r = (pow((mv.m_xt * mv.x) + mv.xt, mv.pt) * mv.m_yt) + mv.yt;
    enemy.getSprite().setPosition(mv.x, -r);
    enemies.push_back(enemy);

    enemies_size += 1;
}


void EnemyManager::updateEnemies(float time) {
    sf::IntRect window_bound(0, 0, 1280, 720);
    int x_max = 1280;
    int y_max = 720;
    if (res.compare("1920x1080") == 0) {
        window_bound = sf::IntRect(0, 0, 1920, 1080);
        x_max = 1920;
        y_max = 1080;
    }

    for (int i = 0; i < enemies_size; i++) {
        Equation mv = enemies[i].getMvmt();
        sf::Sprite sprite = enemies[i].getSprite();

        mv.x += 150 * time;
        enemies[i].setEqX(mv.x);
        float r = (pow((mv.m_xt * mv.x) + mv.xt, mv.pt) * mv.m_yt) + mv.yt;

        sprite.setPosition(mv.x, -r);
        enemies[i].setSprite(sprite);

        if (!window_bound.intersects((sf::IntRect)enemies[i].getSprite().getGlobalBounds())) {
            enemies.erase(enemies.begin() + i);
            i -= 1;
            enemies_size -= 1;
        }
    }
}


void EnemyManager::removeEnemy(int index) {
    enemies.erase(enemies.begin() + index);
    enemies_size -= 1;
}