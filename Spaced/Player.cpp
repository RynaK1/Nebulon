#include "Player.h"

Player::Player() {
    if (!texture.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 1, 31, 27))) {
        std::cerr << "spaceSprites.png file missing" << std::endl;
    }
    sprite.setTexture(texture);

    mvmt_speed = 600;
    sprite.setScale(1.5, 1.5);
    sprite.setOrigin(14, 16);
    sprite.setPosition(640, 540);

    if (readFromFile("resolution").compare("1920x1080") == 0) {
        mvmt_speed = 900;
        sprite.setScale(2.25f, 2.25f);
        sprite.setPosition(960, 810);
    }
}

sf::Sprite Player::getSprite() {
    return sprite;
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


void Player::shoot() {

}