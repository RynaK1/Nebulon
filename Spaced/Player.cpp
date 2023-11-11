#include "Player.h"

Player::Player(sf::Texture& texture, bool fhd) {
    this->fhd = fhd;
    sprite.setTexture(texture);

    mvmt_speed = 400;
    sprite.setScale(0.2f, 0.2f);
    sprite.setPosition(640, 540);

    if (fhd) {
        mvmt_speed = 600;
        sprite.setScale(0.3f, 0.3f);
        sprite.setPosition(960, 810);
        fhd = true;
    }

    health = 100;
}


void Player::setHealth(int health) {
    this->health = health;
}


int Player::getHealth() {
    return health;
}


sf::Sprite Player::getSprite() {
    return sprite;
}


std::vector<Bullet> Player::getBullets() {
    return bulletManager.getBullets();
}


float Player::getCDPercent(int num) {
    float result = 100;
    switch (num) {
    case 1:
        result = shoot1CD.getElapsedTime().asSeconds() / 0.5f;
        break;
    case 2:
        result = shoot2CD.getElapsedTime().asSeconds() / 1.5f;
        break;
    }
    
    if (result > 1) {
        result = 1;
    }

    return result;
}


void Player::move(float time, std::array<bool, 4> bounds) {
    sf::Vector2f vel;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && bounds[0] != false) {
        vel.x -= mvmt_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && bounds[1] != false) {
        vel.x += mvmt_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && bounds[2] != false) {
        vel.y -= mvmt_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && bounds[3] != false) {
        vel.y += mvmt_speed;
    }

    if (vel.x != 0 && vel.y != 0) {
        vel /= std::sqrt(2.0f);
    }

    sprite.move(vel * time);
}


bool Player::shoot(sf::Texture& texture, int type) {
    if (type == 1 && shoot1CD.getElapsedTime().asSeconds() >= 0.5f) {
        bulletManager.shoot(texture, this->getGlobalBounds(), 1);
        shoot1CD.restart();
        return true;
    }
    else if (type == 2 && shoot2CD.getElapsedTime().asSeconds() >= 1.5f) {
        bulletManager.shoot(texture, this->getGlobalBounds(), 2);
        shoot2CD.restart();
        return true;
    }

    return false;
}


void Player::removeBullet(int index) {
    bulletManager.remove(index);
}


void Player::updateBullets(float time) {
    bulletManager.update(time);
}


void Player::playerDamaged(int dmg) {
    if (damagedCD.getElapsedTime().asSeconds() >= 0.5f) {
        setHealth(health - dmg);
        damagedCD.restart();
    }
}


sf::FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}