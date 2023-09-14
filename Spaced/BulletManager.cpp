#include "BulletManager.h"

BulletManager::BulletManager() {
    if (!sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
        std::cerr << "sfx file missing" << std::endl;
    }
    if (!bullet_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6))) {
        std::cerr << "spaceSprites.png file missing <bullet>" << std::endl;
    }
    
    sfx.setBuffer(sfx_buffer);
    sfx.setVolume(calcVolTotal().y);
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

    bullet.setPosition(player_pos.left + 14, player_pos.top - 6);
    bullet.setScale(3, 3);
    if (res.compare("1920x1080") == 0) {
        bullet.setScale(4.5, 4.5);
    }

    bullets.push_back(bullet);
    sfx.play();
    bullets_size += 1;
}


void BulletManager::updateBullets(float time) {
    float speed = -750;
    if (res == "1920x1080") {
        speed = -1125;
    }

    for (int i = 0; i < bullets_size; i++) {
        sf::Vector2f bullet_pos = bullets[i].getPosition();

        if (bullet_pos.y <= -6) {
            bullets.erase(bullets.begin() + i);
            i -= 1;
            bullets_size -= 1;
        }
        else {
            bullets[i].move(0, speed * time);
        }
    }
}