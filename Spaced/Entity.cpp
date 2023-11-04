#include "Entity.h"

Entity::Entity(sf::Texture& texture) {
	sprite.setTexture(texture);
}


void Entity::setRotation(float r) {
	sprite.setRotation(r);
}


void Entity::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}


void Entity::setScale(float s1, float s2) {
	sprite.setScale(s1, s2);
}

sf::FloatRect Entity::getGlobalBounds() {
	return sprite.getGlobalBounds();
}


sf::Vector2f Entity::getScale() {
	return sprite.getScale();
}


sf::Sprite Entity::getSprite() {
	return sprite;
}


//****************************************************************************************


MovingEntity::MovingEntity(Movement mvmt, sf::Texture& texture, float scale, bool fhd) {
	this->mvmt = mvmt;
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	if (fhd == true) {
		sprite.setScale(scale * 1.5f, scale * 1.5f);
	}
}


void MovingEntity::setMvmt(Movement mvmt) {
	this->mvmt = mvmt;
}



sf::Vector2f MovingEntity::update(float time) {
	return mvmt.update(time);
}


//****************************************************************************************


MovingEntityManager::MovingEntityManager(bool fhd) {
	this->fhd = fhd;
	movingEntities_size = 0;
	int flags_size = sizeof(flags);
	for (int i = 0; i < flags_size; i++) {
		flags[i] = false;
	}
}


int MovingEntityManager::getMovingEntities_size() {
	return movingEntities_size;
}


std::vector<MovingEntity> MovingEntityManager::getMovingEntities() {
	return movingEntities;
}


void MovingEntityManager::spawn(MovingEntity me) {
	movingEntities.push_back(me);
	movingEntities_size += 1;
}


void MovingEntityManager::update(float time) {
	sf::IntRect window_bound(0, 0, 1280, 720);
	if (fhd == true) {
		window_bound = sf::IntRect(0, 0, 1920, 1080);
	}

	for (int i = 0; i < movingEntities_size; i++) {
		sf::Vector2f result = movingEntities[i].update(time);
		movingEntities[i].setPosition(result.x, -result.y);
		// bound check
		if (!window_bound.intersects((sf::IntRect)movingEntities[i].getGlobalBounds())) {
			remove(i);
			i -= 1;
		}
	}
}


void MovingEntityManager::remove(int i) {
	movingEntities.erase(movingEntities.begin() + i);
	movingEntities_size -= 1;
}