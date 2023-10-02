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


MovingEntity::MovingEntity(Equation eq, sf::Texture& texture, bool fhd, float scale, float speed) {
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
	float eq_scale = 1;
	if (fhd == true) {
		eq_scale *= 1.5f;
	}

	float time = clock.getElapsedTime().asSeconds();
	if ((int)time == 0 && flags[0] == false) {
		Equation eq0(1, 0 * eq_scale, -300 * eq_scale, 1, 0.23f * (1 / eq_scale), 1279 * eq_scale, true);
		MovingEntity me0(eq0, movingEntities_t[0], fhd, 0.05f, 40.0f);
		me0.setRotation(10.0f);
		movingEntities2.push_back(me0); //top right, small, fast

		Equation eq1(0, 0 * eq_scale, -300 * eq_scale, 0, 0 * (1 / eq_scale), -140 * eq_scale, false);
		MovingEntity me1(eq1, movingEntities_t[1], fhd, 0.3f, 10.0f); //bottom left, lower
		movingEntities1.push_back(me1);

		Equation eq3(0, 0 * eq_scale, -450 * eq_scale, 0, 0 * (1 / eq_scale), 1030 * eq_scale, true);
		MovingEntity me3(eq3, movingEntities_t[3], fhd, 0.15f, 5.0f);
		movingEntities1.push_back(me3); //bottom right, behind tower

		Equation eq4(0, 0 * eq_scale, -100 * eq_scale, 0, 0 * (1 / eq_scale), 1279 * eq_scale, true);
		MovingEntity me4(eq4, movingEntities_t[4], fhd, 0.5f, 20.0f);
		movingEntities2.push_back(me4); //top right, higher

		Equation eq5(0, 0 * eq_scale, -175 * eq_scale, 0, 0 * (1 / eq_scale), 1279 * eq_scale, true);
		MovingEntity me5(eq5, movingEntities_t[5], fhd, 0.5f, 25.0f);
		movingEntities2.push_back(me5); //top right, lower

		Equation eq6(0, 0 * eq_scale, -400 * eq_scale, 0, 0 * (1 / eq_scale), 200 * eq_scale, false);
		MovingEntity me6(eq6, movingEntities_t[6], fhd, 0.10f, 3.0f);
		movingEntities1.push_back(me6); //bottom left, behind tower


		movingEntities1_size += 3;
		movingEntities2_size += 3;
		flags[0] = true;
	}
	else if ((int)time == 10 && flags[1] == false) {
		Equation eq2(0, 0 * eq_scale, -260 * eq_scale, 0, 0 * (1 / eq_scale), -102 * eq_scale, false);
		MovingEntity me2(eq2, movingEntities_t[2], fhd, 0.22f, 10.0f);
		movingEntities1.insert(movingEntities1.begin(), me2);

		movingEntities1_size += 1;
		flags[1] = true;
	}
	else if ((int)time == 120) {
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
		scale = 1.5;
	}

	//back
	for (int i = 0; i < movingEntities1_size; i++) {
		Equation eq = movingEntities1[i].getEquation();
		float speed = movingEntities1[i].getSpeed() * scale;

		if (eq.reverse == false) {
			eq.x += speed * time;
		}
		else {
			eq.x -= speed * time;
		}

		movingEntities1[i].setEqX(eq.x);
		float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

		movingEntities1[i].setPosition(eq.x, -r);

		// bound check
		if (!window_bound.intersects((sf::IntRect)movingEntities1[i].getGlobalBounds())) {
			remove1(i);
			i -= 1;
		}
	}

	//front
	for (int i = 0; i < movingEntities2_size; i++) {
		Equation eq = movingEntities2[i].getEquation();
		float speed = movingEntities2[i].getSpeed() * scale;

		if (eq.reverse == false) {
			eq.x += speed * time;
		}
		else {
			eq.x -= speed * time;
		}

		movingEntities2[i].setEqX(eq.x);
		float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

		movingEntities2[i].setPosition(eq.x, -r);

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

//INHERITANCE TO IMPLEMENT TRANSPARENT RECTS?