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


void BackEntity::setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

sf::FloatRect BackEntity::getGlobalBounds() {
	return sprite.getGlobalBounds();
}

void BackEntity::setEqX(float x) {
	equation.x = x;
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
}


int BackEntityManager::getBackEntities_size() {
	return backEntities_size;
}


std::vector<BackEntity> BackEntityManager::getBackEntities() {
	return backEntities;
}


void BackEntityManager::spawn(Equation eq, sf::Texture& texture, float scale, float s) {
	if (fhd == true) {
		eq.m_yt *= 0.667f;
		eq.xt *= 1.5;
		eq.yt *= 1.5;
	}

	BackEntity backEntity(eq, texture, fhd, scale, s);
	
	float r = (pow((eq.m_xt * eq.x) + eq.xt, eq.pt) * eq.m_yt) + eq.yt;

	backEntity.setPosition(eq.x, -r);
	backEntities.push_back(backEntity);

	backEntities_size += 1;
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