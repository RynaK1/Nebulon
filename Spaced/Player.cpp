#include "Player.h"

Player::Player(sf::Texture& texture) {
    sprite.setTexture(texture);

    mvmt_speed = 600;
    sprite.setScale(1.5, 1.5);
    sprite.setPosition(640, 540);
    fhd = false;

    if (readFromFile("resolution").compare("1920x1080") == 0) {
        mvmt_speed = 900;
        sprite.setScale(2.25, 2.25);
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


void Player::shoot(sf::Texture& texture, int type) {
    if (type == 1 && shoot1CD.getElapsedTime().asSeconds() >= 0.5f) {
        bulletManager.shoot(texture, this->getGlobalBounds(), 1);
        shoot1CD.restart();
    }
    else if (type == 2 && shoot2CD.getElapsedTime().asSeconds() >= 1.5f) {
        bulletManager.shoot(texture, this->getGlobalBounds(), 2);
        shoot2CD.restart();
    }
}


void Player::removeBullet(int index) {
    bulletManager.removeBullet(index);
}


void Player::updateBullets(float time) {
    bulletManager.updateBullets(time);
}


void Player::playerDamaged(int dmg) {
    if (damagedCD.getElapsedTime().asSeconds() >= 0.5f) {
        setHealth(health - dmg);
    }
}


sf::FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}