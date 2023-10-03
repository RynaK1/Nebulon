#include "Enemy.h"

/*
void Enemy::setPosition(float x, float y) {
    sprite.setPosition(x, y);
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

sf::FloatRect Enemy::getGlobalBounds() {
    return sprite.getGlobalBounds();
}


sf::Sprite Enemy::getSprite() {
    return sprite;
}


sf::Vector2f Enemy::update() {

}


void Enemy::attack() {}



EnemyT1::EnemyT1(Movement mvmt, sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(0.25f, 0.25f);
    if (fhd == true) {
        sprite.setScale(0.325f, 0.325f);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    this->mvmt = mvmt;
    type = 1;
    health = 10;
}


void EnemyT1::attack() {

}



EnemyT2::EnemyT2(Movement mvmt, sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(0.18f, 0.18f);
    if (fhd == true) {
        sprite.setScale(0.27f, 0.27f);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setRotation(180);
    this->mvmt = mvmt;
    type = 2;
    health = 15;
}


void EnemyT2::attack() {

}



EnemyBoss::EnemyBoss(Movement mvmt, sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(0.75, 0.75);
    if (fhd == true) {
        sprite.setScale(1.125f, 1.125f);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    this->mvmt = mvmt;
    type = 10;
    health = 100;
}

void EnemyBoss::attack() {

}



EnemyManager::EnemyManager() {
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


void EnemyManager::spawn(Movement mvmt, sf::Texture& texture, int type) {
    Enemy enemy;
    switch (type) {
    case 1:
        enemy = EnemyT1(mvmt, texture, fhd);
        break;
    case 2:
        enemy = EnemyT2(mvmt, texture, fhd);
        break;
    case 10:
        enemy = EnemyBoss(mvmt, texture, fhd);
        break;
    }

    sf::Vector2f result = movingEntities1[i].update();
    movingEntities1[i].setPosition(result.x, -result.y);

    enemy.setPosition(eq.x, -r);
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
        Equation eq = enemies[i].getEquation();

        if (eq.reverse == false) {
            eq.x += 150 * scale * time;
        }
        else if (eq.reverse == true) {
            eq.x -= 150 * scale * time;
        }

        enemies[i].setEqX(eq.x);
        float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

        enemies[i].setPosition(eq.x, -r);

        // bound check
        if (!window_bound.intersects((sf::IntRect)enemies[i].getGlobalBounds())) {
            removeEnemy(i);
            i -= 1;
        }
    }
}


void EnemyManager::removeEnemy(int index) {
    enemies.erase(enemies.begin() + index);
    enemies_size -= 1;
}
*/