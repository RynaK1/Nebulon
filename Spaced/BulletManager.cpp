#include "BulletManager.h"

BulletManager::BulletManager() {
    if (!bullet_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6))) {
        std::cerr << "spaceSprites.png file missing <bullet>" << std::endl;
    }

    res = readFromFile("resolution");
    bullets_size = 0;
}

std::vector<sf::Sprite> BulletManager::getBullets() {
    return bullets;
}

int BulletManager::getBullets_size() {
    return bullets_size;
}


void BulletManager::shoot(sf::FloatRect player_pos) {
    sf::Sprite bullet;
    bullet.setTexture(bullet_t);

    bullet.move(player_pos.left + 14, player_pos.top - 6);
    bullet.setScale(3, 3);
    if (res.compare("1920x1080") == 0) {
        bullet.setScale(4.5, 4.5);
    }

    bullets.push_back(bullet);
    bullets_size += 1;
}


void BulletManager::update() {
    for (int i = 0; i < bullets_size; i++) {
        sf::Vector2f bullet_pos = bullets[i].getPosition();

        if (bullet_pos.y <= -6) {
            bullets.erase(bullets.begin() + i);
            i--;
            bullets_size -= 1;
        }
        else {
            bullets[i].setPosition(bullet_pos.x, bullet_pos.y - 1);
        }
    }
}