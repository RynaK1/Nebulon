#include "Entity.h"

Entity::Entity() {
	fhd = false;
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


MovingEntity::MovingEntity(Equation eq, sf::Texture& texture, bool fhd, float scale, float speed) {
	this->fhd = fhd;
	this->speed = speed;
	equation = eq;
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	if (fhd == true) {
		sprite.setScale(scale * 1.5f, scale * 1.5f);
	}
}


void MovingEntity::setEqX(float x) {
	equation.x = x;
}


float MovingEntity::getSpeed() {
	return speed;
}


Equation MovingEntity::getEquation() {
	return equation;
}



MovingEntityManager::MovingEntityManager() {
	fhd = false;
	movingEntities_size = 0;
	int flags_size = sizeof(flags);
	for (int i = 0; i < flags_size; i++) {
		flags[i] = false;
	}
}


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


void MovingEntityManager::spawn(sf::Texture* movingEntities_t) {
	float eq_scale = 1;
	if (fhd == true) {
		eq_scale *= 1.5f;
	}
	
	//ships
	float time = clock.getElapsedTime().asSeconds();
	if ((int)time == 0 && flags[0] == false) {
		Equation eq1(0, 0 * eq_scale, -300 * eq_scale, 0, 0 * (1 / eq_scale), -140 * eq_scale, false);
		MovingEntity me1(eq1, movingEntities_t[1], fhd, 0.3f, 10.0f);
		movingEntities.push_back(me1);

		Equation eq2(0, 0 * eq_scale, -450 * eq_scale, 0, 0 * (1 / eq_scale), 1030 * eq_scale, true);
		MovingEntity me2(eq2, movingEntities_t[3], fhd, 0.15f, 5.0f);
		movingEntities.push_back(me2);

		Equation eq3(1, 0 * eq_scale, -300 * eq_scale, 1, 0.23f * (1 / eq_scale), 1279 * eq_scale, true);
		MovingEntity me3(eq3, movingEntities_t[0], fhd, 0.05f, 40.0f);
		me3.setRotation(10.0f);
		movingEntities.push_back(me3);


		Equation eq4(0, 0 * eq_scale, -100 * eq_scale, 0, 0 * (1 / eq_scale), 1279 * eq_scale, true);
		MovingEntity me4(eq4, movingEntities_t[4], fhd, 0.5f, 20.0f);
		movingEntities.push_back(me4);

		Equation eq5(0, 0 * eq_scale, -200 * eq_scale, 0, 0 * (1 / eq_scale), 1279 * eq_scale, true);
		MovingEntity me5(eq5, movingEntities_t[5], fhd, 0.5f, 30.0f);
		movingEntities.push_back(me5);

		movingEntities_size += 5;
		flags[0] = true;
	}
	else if ((int)time == 10 && flags[1] == false) {
		Equation eq1(0, 0 * eq_scale, -260 * eq_scale, 0, 0 * (1 / eq_scale), -102 * eq_scale, false);
		MovingEntity me1(eq1, movingEntities_t[2], fhd, 0.22f, 10.0f);
		movingEntities.push_back(me1);

		movingEntities_size += 1;
		flags[1] = true;
	}
	else if ((int)time == 140) {
		int flags_size = sizeof(flags);
		for (int i = 0; i < flags_size; i++) {
			flags[i] = false;
		}
		clock.restart();
	}
}


void MovingEntityManager::updateMovingEntities(float time) {
	sf::IntRect window_bound(0, 0, 1280, 720);
	float scale = 1;
	if (fhd == true) {
		window_bound = sf::IntRect(0, 0, 1920, 1080);
		scale = 1.5;
	}

	for (int i = 0; i < movingEntities_size; i++) {
		Equation eq = movingEntities[i].getEquation();
		float speed = movingEntities[i].getSpeed() * scale;

		if (eq.reverse == false) {
			eq.x += speed * time;
		}
		else {
			eq.x -= speed * time;
		}

		movingEntities[i].setEqX(eq.x);
		float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

		movingEntities[i].setPosition(eq.x, -r);

		// bound check
		if (!window_bound.intersects((sf::IntRect)movingEntities[i].getGlobalBounds())) {
			removeMovingEntity(i);
			i -= 1;
		}
	}
}


void MovingEntityManager::removeMovingEntity(int i) {
	movingEntities.erase(movingEntities.begin() + i);
	movingEntities_size -= 1;
}

//INHERITANCE TO IMPLEMENT TRANSPARENT RECTS?