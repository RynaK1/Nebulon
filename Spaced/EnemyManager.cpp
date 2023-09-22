#include "EnemyManager.h"

Enemy::Enemy() {
    type = 0;
    health = 0;
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


void Enemy::setHealth(int health) {
    this->health = health;
}


int Enemy::getHealth() {
    return health;
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
    health = 10;
}


void EnemyT1::attack() {

}



EnemyT2::EnemyT2(Equation mv) {
    sprite.setOrigin(15, 15);
    type = 2;
    mvmt = mv;
    health = 15;
}


void EnemyT2::attack() {

}



EnemyBoss::EnemyBoss(Equation mv) {
    sprite.setOrigin(91, 166);
    type = 10;
    mvmt = mv;
    health = 100;
}

void EnemyBoss::attack() {

}



EnemyManager::EnemyManager() {
    enemy_t1.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 48, 23, 28));
    enemy_t2.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(25, 48, 30, 29));
    enemy_boss.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 80, 182, 332));
    
    fhd = false;
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        fhd = true;
    }
    enemies_size = 0;
}


void EnemyManager::setEnemyHealth(int health, int index) {
    enemies[index].setHealth(health);
}


int EnemyManager::getEnemies_size() {
    return enemies_size;
}


std::vector<Enemy> EnemyManager::getEnemies() {
    return enemies;
}


void EnemyManager::spawn(int type, Equation eq) {
    if (fhd == true) {
        eq.m_yt *= 0.667f;
        eq.xt *= 1.5;
        eq.yt *= 1.5;
    }

    Enemy enemy;
    switch (type) {
    case 1:
        enemy = EnemyT1(eq);
        enemy.getSprite().setTexture(enemy_t1);
        break;
    case 2:
        enemy = EnemyT2(eq);
        enemy.getSprite().setTexture(enemy_t2);
        break;
    case 10:
        enemy = EnemyBoss(eq);
        enemy.getSprite().setTexture(enemy_boss);
        break;
    }

    float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

    enemy.getSprite().setPosition(eq.x, -r);
    enemies.push_back(enemy);

    enemies_size += 1;
}


void EnemyManager::updateEnemies(float time) {
    sf::IntRect window_bound(0, 0, 1280, 720);
    float scale = 1;
    if (fhd == true) {
        window_bound = sf::IntRect(0, 0, 1920, 1080);
        scale = 1.5;
    }

    for (int i = 0; i < enemies_size; i++) {
        Equation eq = enemies[i].getMvmt();
        sf::Sprite sprite = enemies[i].getSprite();

        eq.x += (150 * scale) * time;
        enemies[i].setEqX(eq.x);
        float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

        sprite.setPosition(eq.x, -r);
        enemies[i].setSprite(sprite);

        // bound check
        if (!window_bound.intersects((sf::IntRect)enemies[i].getSprite().getGlobalBounds())) {
            removeEnemy(i);
            i -= 1;
        }
    }
}


void EnemyManager::removeEnemy(int index) {
    enemies.erase(enemies.begin() + index);
    enemies_size -= 1;
}