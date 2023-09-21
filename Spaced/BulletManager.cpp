#include "BulletManager.h"

BulletManager::BulletManager() {   
    num_bullets = 0;
    fhd = false;
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        fhd = true;
    }
}


std::vector<Bullet> BulletManager::getBullets() {
    return bullets;
}


void BulletManager::shoot(sf::Texture& texture, sf::FloatRect player_pos, int type) {
    Bullet bullet;
    if (type == 1) {
        bullet = smallBullet(texture, fhd);
    }
    else if (type == 2) {
        bullet = largeBullet(texture, fhd);
    }

    bullet.setPosition(player_pos.left + (player_pos.width / 2), player_pos.top - 3); // y-coord offset

    bullets.push_back(bullet);
    num_bullets += 1;

    sfx.play();
}


void BulletManager::updateBullets(float time) {
    sf::FloatRect window_bound(0, 0, 1280, 720);

    if (fhd == true) {
        window_bound = sf::FloatRect(0, 0, 1920, 1080);
    }

    for (int i = 0; i < num_bullets; i++) {
        if (!window_bound.intersects(bullets[i].getGlobalBounds())) {
            removeBullet(i);
            i -= 1;
        }
        else { 
            bullets[i].move(0, -bullets[i].getSpeed() * time);
        }
    }
}


void BulletManager::removeBullet(int index) {
    bullets.erase(bullets.begin() + index);
    num_bullets -= 1;
}



Bullet::Bullet() {
    damage = 0;
    speed = 0;
    type = 0;
}


void Bullet::setScale(float x, float y) {
    sprite.setScale(x, y);
}


void Bullet::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}


int Bullet::getDamage() {
    return damage;
}


int Bullet::getType() {
    return type;
}


int Bullet::getSpeed() {
    return speed;
}


sf::Sprite Bullet::getSprite() {
    return sprite;
}


sf::FloatRect Bullet::getGlobalBounds() {
    return sprite.getGlobalBounds();
}


void Bullet::move(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}



smallBullet::smallBullet(sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(3, 3);
    sprite.setOrigin(1.5, 3);

    damage = 10;
    type = 1;
    speed = 900;

    if (fhd == true) {
        sprite.setScale(4.5, 4.5);
        speed = 1350;
    }
}


largeBullet::largeBullet(sf::Texture& texture, bool fhd) {
    sprite.setTexture(texture);
    sprite.setScale(3, 3);
    sprite.setOrigin(2.5, 5.5);

    damage = 25;
    type = 2;
    speed = 650;

    if (fhd == true) {
        sprite.setScale(4.5, 4.5);
        speed = 975;
    }
}