#include "Entity.h"


Equation::Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x_max, float speed_mult, bool reverse) {
	this->pt = pt;
	this->xt = xt;
	this->yt = yt;
	this->m_xt = m_xt;
	this->m_yt = m_yt;
	this->x_max = x_max;
	this->speed_mult = speed_mult;
	this->negative = reverse;
}



Entity::Entity(sf::Texture& texture, float pos_x, float speed) {
	sprite.setTexture(texture);
	this->pos_x = pos_x;
	this->speed = speed;
	eq_curr = 0;
}


void Entity::setEqs(std::vector<Equation> eqs) {
	this->eqs = eqs;
}


void Entity::setRotation(float r) {
	sprite.setRotation(r);
}


void Entity::setPos_x(float pos_x) {
	this->pos_x = pos_x;
}


void Entity::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}


void Entity::setScale(float s1, float s2) {
	sprite.setScale(s1, s2);
}


void Entity::setSpeed(float speed) {
	this->speed = speed;
}


sf::FloatRect Entity::getGlobalBounds() {
	return sprite.getGlobalBounds();
}


sf::Vector2f Entity::getPosition() {
	return sprite.getPosition();
}


sf::Sprite Entity::getSprite() {
	return sprite;
}


sf::Vector2f Entity::getScale() {
	return sprite.getScale();
}


float Entity::getSpeed() {
	return speed;
}


std::vector<Equation> Entity::getEqs() {
	return eqs;
}


float Entity::getPos_x() {
	return pos_x;
}


sf::Vector2f Entity::update(float time) {
	if (eqs[eq_curr].negative == true) {
		pos_x -= speed * time;
	}
	else {
		pos_x += speed * time;
	}

	if ((eqs[eq_curr].negative == false && pos_x >= eqs[eq_curr].x_max) ||
		(eqs[eq_curr].negative == true && pos_x <= eqs[eq_curr].x_max)) {
		eq_curr += 1;
		speed *= eqs[eq_curr].speed_mult;
	};

	float pos_y;
	pos_y = (pow((eqs[eq_curr].m_xt * pos_x) + eqs[eq_curr].xt, eqs[eq_curr].pt) * eqs[eq_curr].m_yt) + eqs[eq_curr].yt;
	return sf::Vector2f(pos_x, pos_y);
}


void Entity::push_back(Equation eq) {
	eqs.push_back(eq);
}



EntityManager::EntityManager(bool fhd) {
	boundary = sf::IntRect(0, 0, 1280, 720);
	if (fhd) {
		boundary = sf::IntRect(0, 0, 1920, 1080);
	}
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
	for (int i = 0; i < size; i++) {
		sf::Vector2f result = entities[i].update(time);
		entities[i].setPosition(result.x, -result.y);
		// bound check
		if (!boundary.intersects((sf::IntRect)entities[i].getGlobalBounds())) {
			remove(i);
			i -= 1;
		}
	}
}