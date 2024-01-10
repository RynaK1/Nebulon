#include "Enemy.h"

/*
void Enemy::setHealth(int health) {
    this->health = health;
}


BulletManager* Enemy::getBulletManager() {
    return &bulletManager;
}


int Enemy::getHealth() {
    return health;
}


int Enemy::getValue() {
    return value;
}


void Enemy::updateBullets(float time) {
    bulletManager.update(time);
}


bool Enemy::isBoss() {
    return boss;
}



Enemy0::Enemy0(sf::Texture& body_texture, sf::Texture& attack_texture) {
    sprite.setTexture(body_texture);
    sprite.setScale(0.25f, 0.25f);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    health = 10;
    value = 0;
    boss = false;
}


void Enemy0::attack() {
    float time = clock.getElapsedTime().asSeconds();
    if ((int)time == 1 && flag == false) {
        bulletManager.shoot(*attack_texture, sprite.getGlobalBounds(), 3);
        flag = true;
    }
    else if ((int)time == 3) {
        clock.restart();
        flag = false;
    }
}



Enemy1::Enemy1(sf::Texture& body_texture, sf::Texture& attack_texture) {
    sprite.setTexture(body_texture);
    sprite.setScale(0.18f, 0.18f);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    sprite.setRotation(180);
    health = 15;
    value = 0;
    boss = false;
}



EnemyBoss::EnemyBoss(sf::Texture& body_texture, sf::Texture& attack_texture) {
    sprite.setTexture(body_texture);
    sprite.setScale(0.75, 0.75);
    sprite.setOrigin(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
    health = 150;
    value = 10;
    boss = true;
}

void EnemyBoss::attack() {

}


/*
EnemyManager::EnemyManager(bool fhd) {
    if (fhd) {
        boundary = sf::IntRect(0, 0, 1920, 1080);
    }
    boundary = sf::IntRect(0, 0, 1280, 720);
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


void EnemyManager::push_back(Enemy enemy) {
    enemies.push_back(enemy);
    enemies_size += 1;
}


void EnemyManager::update(float time) {
    for (int i = 0; i < enemies_size; i++) {
        sf::Vector2f result = enemies[i].update(time);
        enemies[i].setPosition(result.x, -result.y);
        enemies[i].attack(texture);
        enemies[i].updateBullets(time);
        // bound check
        if (!boundary.intersects((sf::IntRect)enemies[i].getGlobalBounds())) {
            remove(i);
            i -= 1;
        }
    }
}


void EnemyManager::remove(int i) {
    enemies.erase(enemies.begin() + i);
    enemies_size -= 1;
}
*/