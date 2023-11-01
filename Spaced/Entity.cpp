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


MovingEntityManager::MovingEntityManager(sf::Texture* movingEntities_t, bool fhd) {
	this->fhd = fhd;
	movingEntities1_size = 0;
	movingEntities2_size = 0;
	int flags_size = sizeof(flags);
	for (int i = 0; i < flags_size; i++) {
		flags[i] = false;
	}
}


int MovingEntityManager::getMovingEntities1_size() {
	return movingEntities1_size;
}


int MovingEntityManager::getMovingEntities2_size() {
	return movingEntities2_size;
}



std::vector<MovingEntity> MovingEntityManager::getMovingEntities1() {
	return movingEntities1;
}


std::vector<MovingEntity> MovingEntityManager::getMovingEntities2() {
	return movingEntities2;
}


void MovingEntityManager::spawn(sf::Texture* movingEntities_t) {
	float MAX = 9999;
	float MIN = -1000;
	float eq_scale = 1;
	if (fhd == true) {
		eq_scale *= 1.5f;
	}

	float time = clock.getElapsedTime().asSeconds();
	if ((int)time == 0 && flags[0] == false) {
		//          pt, xt, yt, m_xt, m_yt, x_max, speed, reverse, fhd
		Equation eq0(1, 0, -300, 1, 0.23f, MIN, 40 ,true, fhd);
		Movement mvmt0(1280, fhd);
		mvmt0.push_back(eq0);
		MovingEntity me0(mvmt0, movingEntities_t[0], 0.07f, fhd); //top right, fast
		movingEntities2.push_back(me0);

		Equation eq1(0, 0, -300, 0, 0, MAX, 10, false, fhd);
		Movement mvmt1(-135, fhd);
		mvmt1.push_back(eq1);
		MovingEntity me1(mvmt1, movingEntities_t[1], 0.3f, fhd); //bottom left, lower
		movingEntities1.push_back(me1);

		Equation eq3(0, 0, -450, 0, 0, MIN, 5, true, fhd);
		Movement mvmt3(1020, fhd);
		mvmt3.push_back(eq3);
		MovingEntity me3(mvmt3, movingEntities_t[3], 0.2f, fhd);
		movingEntities1.push_back(me3); //bottom right, behind tower

		Equation eq4(0, 0, -100, 0, 0, MIN, 25, true, fhd);
		Movement mvmt4(1280, fhd);
		mvmt4.push_back(eq4);
		MovingEntity me4(mvmt4, movingEntities_t[4], 0.5f, fhd);
		movingEntities2.push_back(me4); //top right, higher

		Equation eq5(0, 0, -175, 0, 0, MIN, 20, true, fhd);
		Movement mvmt5(1280, fhd);
		mvmt5.push_back(eq5);
		MovingEntity me5(mvmt5, movingEntities_t[5], 0.5f, fhd);
		movingEntities2.push_back(me5); //top right, lower

		Equation eq6(0, 0, -400, 0, 0, MAX, 3, false, fhd);
		Movement mvmt6(200, fhd);
		mvmt6.push_back(eq6);
		MovingEntity me6(mvmt6, movingEntities_t[6], 0.10f, fhd);
		movingEntities1.push_back(me6); //bottom left, behind tower

		movingEntities1_size += 3;
		movingEntities2_size += 3;
		flags[0] = true;
	}
	else if ((int)time == 10 && flags[1] == false) {
		Equation eq2(0, 0, -260, 0, 0, MAX, 10, false, fhd);
		Movement mvmt2(-102, fhd);
		mvmt2.push_back(eq2);
		MovingEntity me2(mvmt2, movingEntities_t[2], 0.22f, fhd);
		movingEntities1.push_back(me2);

		movingEntities1_size += 1;
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


void MovingEntityManager::update(float time) {
	sf::IntRect window_bound(0, 0, 1280, 720);
	float scale = 1;
	if (fhd == true) {
		window_bound = sf::IntRect(0, 0, 1920, 1080);
		scale = 1.5f;
	}

	//back
	for (int i = 0; i < movingEntities1_size; i++) {
		sf::Vector2f result = movingEntities1[i].update(time);
		movingEntities1[i].setPosition(result.x, -result.y);
		// bound check
		if (!window_bound.intersects((sf::IntRect)movingEntities1[i].getGlobalBounds())) {
			remove1(i);
			i -= 1;
		}
	}

	//front
	for (int i = 0; i < movingEntities2_size; i++) {
		sf::Vector2f result = movingEntities2[i].update(time);
		movingEntities2[i].setPosition(result.x, -result.y);
		// bound check
		if (!window_bound.intersects((sf::IntRect)movingEntities2[i].getGlobalBounds())) {
			remove2(i);
			i -= 1;
		}
	}
}


void MovingEntityManager::remove1(int i) {
	movingEntities1.erase(movingEntities1.begin() + i);
	movingEntities1_size -= 1;
}


void MovingEntityManager::remove2(int i) {
	movingEntities2.erase(movingEntities2.begin() + i);
	movingEntities2_size -= 1;
}