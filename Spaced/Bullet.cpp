#include "Bullet.h"

Bullet::Bullet() {
	damage = 0;
	speed = 0;
	type = 0;
}


void Bullet::setPosition(float x, float y) {
	sprite.setPosition(x, y);
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



smallBullet::smallBullet(bool fhd) {
	if (!sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
		std::cerr << "sfx file missing <bullet>" << std::endl;
	}
	sfx.setBuffer(sfx_buffer);
	sprite.setTexture(texture);

	damage = 10;
	type = 1;
	speed = 900;

	if (fhd == true) {
		speed = 1350;
	}
}


largeBullet::largeBullet(bool fhd) {
	if (!sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
		std::cerr << "sfx file missing <bullet>" << std::endl;
	}
	sfx.setBuffer(sfx_buffer);
	sprite.setTexture(texture);

	damage = 25;
	type = 2;
	speed = 650; 

	if (fhd == true) {
		speed = 975;
	}
}