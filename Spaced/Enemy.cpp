#include "Enemy.h"

void Enemy::setHealth(int health) {
    this->health = health;
}



int Enemy::getHealth() {
    return health;
}


int Enemy::getValue() {
    return value;
}


Enemy0::Enemy0(Movement mvmt, sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(0.25f, 0.25f);
    if (fhd == true) {
        sprite.setScale(0.325f, 0.325f);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    value = 1;
    health = 10;
    this->mvmt = mvmt;
}


void Enemy0::attack(sf::Texture texture) {
    int time = (int)clock.getElapsedTime().asSeconds();
    std::cout << "met" << std::endl;
    if (time == 1 && flag == false) {
        bulletManager.shoot(texture, sprite.getGlobalBounds(), 3);
        flag = true;
    }
    else if (time == 3) {
        clock.restart();
        flag = false;
    }
}



Enemy1::Enemy1(Movement mvmt, sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(0.18f, 0.18f);
    if (fhd == true) {
        sprite.setScale(0.27f, 0.27f);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setRotation(180);
    value = 1;
    health = 15;
    this->mvmt = mvmt;
}


void Enemy1::attack(sf::Texture texture) {

}



EnemyBoss::EnemyBoss(Movement mvmt, sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(0.75, 0.75);
    if (fhd == true) {
        sprite.setScale(1.125f, 1.125f);
    }
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    value = 10;
    health = 100;
    this->mvmt = mvmt;
}

void EnemyBoss::attack(sf::Texture texture) {

}



EnemyManager::EnemyManager(bool fhd) {
    this->fhd = fhd;
    enemies_size = 0;
}


void EnemyManager::setEnemyHealth(int health, int index) {
    enemies[index].setHealth(health);
}


Enemy EnemyManager::getEnemy(int i) {
    return enemies[i];
}


int EnemyManager::getEnemies_size() {
    return enemies_size;
}


std::vector<Enemy> EnemyManager::getEnemies() {
    return enemies;
}


void EnemyManager::spawn(Enemy enemy) {
    enemies.push_back(enemy);
    enemies_size += 1;
}


void EnemyManager::update(float time, sf::Texture& texture) {
    sf::IntRect window_bound(0, 0, 1280, 720);
    float scale = 1;
    if (fhd == true) {
        window_bound = sf::IntRect(0, 0, 1920, 1080);
        scale = 1.5f;
    }

    for (int i = 0; i < enemies_size; i++) {
        sf::Vector2f result = enemies[i].update(time);
        enemies[i].setPosition(result.x, -result.y);
        enemies[i].attack(texture);
        // bound check
        if (!window_bound.intersects((sf::IntRect)enemies[i].getGlobalBounds())) {
            remove(i);
            i -= 1;
        }
    }
}


void EnemyManager::remove(int index) {
    enemies.erase(enemies.begin() + index);
    enemies_size -= 1;
}