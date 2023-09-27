#include "BackEntityManager.h"

BackEntity::BackEntity(Equation eq, sf::Texture& texture, bool fhd, float scale, float s) {
	equation = eq;
	speed = s;
	sprite.setTexture(texture);
	sprite.setScale(scale, scale);
	if (fhd == true) {
		sprite.setScale(scale * 1.5f, scale * 1.5f);
	}
}


void BackEntity::setRotation(float r) {
	sprite.setRotation(r);
}


void BackEntity::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}


void BackEntity::setScale(float s1, float s2) {
	sprite.setScale(s1, s2);
}

sf::FloatRect BackEntity::getGlobalBounds() {
	return sprite.getGlobalBounds();
}

void BackEntity::setEqX(float x) {
	equation.x = x;
}


sf::Vector2f BackEntity::getScale() {
	return sprite.getScale();
}


float BackEntity::getSpeed() {
	return speed;
}


sf::Sprite BackEntity::getSprite() {
	return sprite;
}

Equation BackEntity::getEquation() {
	return equation;
}



BackEntityManager::BackEntityManager(bool fhd) {
	this->fhd = fhd;
	backEntities_size = 0;
	int flags_size = sizeof(flags);
	for (int i = 0; i < flags_size; i++) {
		flags[i] = false;
	}
}


int BackEntityManager::getBackEntities_size() {
	return backEntities_size;
}


std::vector<BackEntity> BackEntityManager::getBackEntities() {
	return backEntities;
}


void BackEntityManager::spawn(sf::Texture* backEntities_t) {
	float eq_scale = 1;
	if (fhd == true) {
		eq_scale *= 1.5f;
	}
	
	//ships
	float time = clock.getElapsedTime().asSeconds();
	if ((int)time == 0 && flags[0] == false) {
		Equation eq1(0, 0 * eq_scale, -300 * eq_scale, 0, 0 * (1 / eq_scale), -140 * eq_scale, false);
		BackEntity backEntity1(eq1, backEntities_t[1], fhd, 0.3f, 10.0f);
		backEntities.push_back(backEntity1);

		Equation eq2(0, 0 * eq_scale, -450 * eq_scale, 0, 0 * (1 / eq_scale), 1030 * eq_scale, true);
		BackEntity backEntity2(eq2, backEntities_t[3], fhd, 0.15f, 5.0f);
		backEntities.push_back(backEntity2);

		Equation eq3(1, 0 * eq_scale, -300 * eq_scale, 1, 0.23f * (1 / eq_scale), 1279 * eq_scale, true);
		BackEntity backEntity3(eq3, backEntities_t[0], fhd, 0.05f, 30.0f);
		backEntity3.setRotation(10.0f);
		backEntities.push_back(backEntity3);


		Equation eq4(0, 0 * eq_scale, -100 * eq_scale, 0, 0 * (1 / eq_scale), 1279 * eq_scale, true);
		BackEntity backEntity4(eq4, backEntities_t[4], fhd, 0.5f, 20.0f);
		backEntities.push_back(backEntity4);

		Equation eq5(0, 0 * eq_scale, -200 * eq_scale, 0, 0 * (1 / eq_scale), 1279 * eq_scale, true);
		BackEntity backEntity5(eq5, backEntities_t[5], fhd, 0.5f, 30.0f);
		backEntities.push_back(backEntity5);

		backEntities_size += 5;
		flags[0] = true;
	}
	else if ((int)time == 10 && flags[1] == false) {
		Equation eq1(0, 0 * eq_scale, -260 * eq_scale, 0, 0 * (1 / eq_scale), -70 * eq_scale, false);
		BackEntity backEntity1(eq1, backEntities_t[2], fhd, 0.22f, 10.0f);
		backEntities.push_back(backEntity1);

		backEntities_size += 1;
		flags[1] = true;
	}
	else if ((int)time == 140) {
		int flags_size = sizeof(flags);
		for (int i = 0; i < flags_size; i++) {
			flags[i] = false;
		}
		clock.restart();
	}

	std::cout << "met" << std::endl;
}


void BackEntityManager::updateBackEntities(float time) {
	sf::IntRect window_bound(0, 0, 1280, 720);
	float scale = 1;
	if (fhd == true) {
		window_bound = sf::IntRect(0, 0, 1920, 1080);
		scale = 1.5;
	}

	for (int i = 0; i < backEntities_size; i++) {
		Equation eq = backEntities[i].getEquation();
		float speed = backEntities[i].getSpeed() * scale;

		if (eq.reverse == false) {
			eq.x += speed * time;
		}
		else {
			eq.x -= speed * time;
		}

		backEntities[i].setEqX(eq.x);
		float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

		backEntities[i].setPosition(eq.x, -r);

		// bound check
		if (!window_bound.intersects((sf::IntRect)backEntities[i].getGlobalBounds())) {
			removeBackEntity(i);
			i -= 1;
		}
	}
}


void BackEntityManager::removeBackEntity(int i) {
	backEntities.erase(backEntities.begin() + i);
	backEntities_size -= 1;
}

//INHERITANCE TO IMPLEMENT TRANSPARENT RECTS?