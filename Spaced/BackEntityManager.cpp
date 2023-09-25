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



BackEntityManager::BackEntityManager() {
	fhd = false;
	if (readFromFile("resolution").compare("1920x1080") == 0) {
		fhd = true;
	}
	backEntities_size = 0;
	int flags_size = sizeof(flags);
	for (int i = 0; i < flags_size; i++) {
		flags[i] = false;
	}
}


void BackEntityManager::setFHD(bool fhd) {
	this->fhd = fhd;
}


int BackEntityManager::getBackEntities_size() {
	return backEntities_size;
}


std::vector<BackEntity> BackEntityManager::getBackEntities() {
	return backEntities;
}


void BackEntityManager::spawn(std::array<sf::Texture, 5>& backEntities_t) {
	float eq_scale = 1;
	if (fhd == true) {
		eq_scale *= 1.5f;
	}
	
	float time = clock.getElapsedTime().asSeconds();
	if ((int)time == 0 && flags[0] == false) {
		Equation eq1(1, 0 * eq_scale, -300 * eq_scale, 1, 0.23f * (1 / eq_scale), 1279 * eq_scale, true);
		BackEntity backEntity1(eq1, backEntities_t[0], fhd, 0.05f, 30.0f);
		backEntity1.setRotation(10.0f);
		backEntities.push_back(backEntity1);

		Equation eq2(0, 0 * eq_scale, -300 * eq_scale, 0, 0 * (1 / eq_scale), -140 * eq_scale, false);
		BackEntity backEntity2(eq2, backEntities_t[1], fhd, 0.3f, 10.0f);
		backEntities.push_back(backEntity2);

		backEntities_size += 2;
		flags[0] = true;
	}
	else if ((int)time == 120) {
		int flags_size = sizeof(flags);
		for (int i = 0; i < flags_size; i++) {
			flags[i] = false;
		}
		clock.restart();
	}
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


void BackEntityManager::resetBackEntities() {
	backEntities.erase(backEntities.begin(), backEntities.end());
	clock.restart();
	backEntities_size = 0;
	
	int flags_size = sizeof(flags);
	for (int i = 0; i < flags_size; i++) {
		flags[i] = false;
	}
}