#include "Player.h"

Player::Player() {
    if (!texture.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 1, 31, 27))) {
        std::cerr << "spaceSprites.png file missing" << std::endl;
    }
    sprite.setTexture(texture);

    mvmt_speed = 600;
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        mvmt_speed = 900;
    }
}

sf::Sprite Player::getSprite() {
    return sprite;
}

void Player::move(float time) {
    sf::Vector2f vel;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        vel.y -= mvmt_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        vel.x -= mvmt_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        vel.y += mvmt_speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        vel.x += mvmt_speed;
    }

    if (vel.x != 0 && vel.y != 0) {
        vel /= std::sqrt(2.0f);
    }

    //std::cout << vel.x << " " << vel.y << std::endl;
    sprite.move(vel * time);

    std::cout << vel.x << " " << vel.y  << std::endl;
}