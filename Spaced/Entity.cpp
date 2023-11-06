#include "Entity.h"

Entity::Entity(Movement mvmt, sf::Texture& texture) {
	this->mvmt = mvmt;
	sprite.setTexture(texture);
}


sf::FloatRect Entity::getGlobalBounds() {
	return sprite.getGlobalBounds();
}


sf::Sprite Entity::getSprite() {
	return sprite;
}


void Entity::setMvmt(Movement mvmt) {
	this->mvmt = mvmt;
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


sf::Vector2f Entity::update(float time) {
	return mvmt.update(time);
}



EntityManager::EntityManager(bool fhd) {
	this->fhd = fhd;
	size = 0;
}


int EntityManager::getSize() {
	return size;
}


std::vector<Entity> EntityManager::getEntities() {
	return entities;
}


void EntityManager::setRotation(int i, float num) {
	entities[i].setRotation(num);
}


void EntityManager::spawn(Entity me) {
	entities.push_back(me);
	size += 1;
}


void EntityManager::remove(int i) {
	entities.erase(entities.begin() + i);
	size -= 1;
}


void EntityManager::update(float time) {
	sf::IntRect window_bound(0, 0, 1280, 720);
	if (fhd == true) {
		window_bound = sf::IntRect(0, 0, 1920, 1080);
	}

	for (int i = 0; i < size; i++) {
		sf::Vector2f result = entities[i].update(time);
		entities[i].setPosition(result.x, -result.y);
		// bound check
		if (!window_bound.intersects((sf::IntRect)entities[i].getGlobalBounds())) {
			remove(i);
			i -= 1;
		}
	}
}