#include "Entity.h"


Equation::Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x_max, float speed_mult, bool isNegative) {
	this->pt = pt;
	this->xt = xt;
	this->yt = yt;
	this->m_xt = m_xt;
	this->m_yt = m_yt;
	this->x_max = x_max;
	this->speed_mult = speed_mult;
	this->isNegative = isNegative;
}



Entity::Entity(sf::Texture& texture, float x, float speed) {
	sprite.setTexture(texture);
	sprite.setPosition(x, 0);
	this->speed = speed;
}

void Entity::setEqs(std::vector<Equation> eqs) {
	this->eqs = eqs;
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

void Entity::setSpeed(float speed) {
	this->speed = speed;
}

void Entity::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
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

void Entity::update(float time) {
	float x = sprite.getPosition().x;
	if (eqs[0].isNegative) {
		x -= speed * time;
	}
	else {
		x += speed * time;
	}

	if ((!eqs[0].isNegative && x >= eqs[0].x_max) ||
		(eqs[0].isNegative && x <= eqs[0].x_max)) {
		speed *= eqs[1].speed_mult;
		eqs.erase(eqs.begin());
	};

	//2nd parameter: y = mx + b
	sprite.setPosition(x, calcYPosition(x));
}

void Entity::push_back(Equation eq) {
	eqs.push_back(eq);
}

float Entity::calcYPosition(float x) {
	return -((pow((eqs[0].m_xt * x) + eqs[0].xt, eqs[0].pt) * eqs[0].m_yt) + eqs[0].yt);
}

void Entity::changeResolution(bool fhd) {
	float val1;
	float val2;
	if (fhd) {
		val1 = 1.5f;
		val2 = 2.255f;
	}
	else {
		val1 = 0.6667f;
		val2 = 0.4433f;
	}

	//change member variables
	speed = speed * val1;
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x * val1, calcYPosition(pos.x * val1));
	sf::Vector2f scale = sprite.getScale();
	sprite.setScale(scale.x * val1, scale.y * val1);

	//change equations
	size_t eqs_size = eqs.size();
	for (int i = 0; i< eqs_size; i++) {
		if (eqs[i].pt == 2) {
			eqs[i].m_yt *= val1;
		}
		else if (eqs[i].pt == 3) {
			eqs[i].m_yt *= val2;
		}
		eqs[i].xt *= val1;
		eqs[i].yt *= val1;
	}
}



GameEntity::GameEntity(sf::Texture& texture, float x, float speed, int health) {
	sprite.setTexture(texture);
	sprite.setPosition(x, 0);
	this->speed = speed;
	this->health = health;
}

void GameEntity::setHealth(int health) {
	this->health = health;
}

int GameEntity::getHealth() {
	return health;
}



Player::Player(sf::Texture& texture, int health) {
	sprite.setTexture(texture);
	sprite.setPosition(640, 600);
	this->speed = 500;
	this->health = health;
}

void Player::move(float time) {
	sf::Vector2f velocity;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		velocity.y -= speed * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		velocity.y += speed * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		velocity.x -= speed * time;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		velocity.x += speed * time;
	}

	if (velocity.x != 0 && velocity.y != 0) {
		velocity.x /= (float)std::sqrt(2);
		velocity.y /= (float)std::sqrt(2);
	}
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x + velocity.x, pos.y + velocity.y);
}

void Player::keepInBoundary(sf::FloatRect boundary) {
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sf::Vector2f adjust;
	if (bounds.left < 0) {
		adjust.x += -bounds.left;
	}
	else if (bounds.left + bounds.width > boundary.width) {
		adjust.x -= bounds.left + bounds.width - boundary.width;
	}

	if (bounds.top < 0) {
		adjust.y += -bounds.top;
	}
	else if (bounds.top + bounds.height > boundary.height) {
		adjust.y -= bounds.top + bounds.height - boundary.height;
	}
	sf::Vector2f pos = sprite.getPosition();
	sprite.setPosition(pos.x + adjust.x, pos.y + adjust.y);
}

bool Player::attack(int type) {
	switch (type) {
	case 0:
		if (attack1_clock.getElapsedTime().asSeconds() >= 1) {
			attack1_clock.restart();
			return true;
		}
		break;
	case 1:
		if (attack1_clock.getElapsedTime().asSeconds() >= 2.5) {
			attack2_clock.restart();
			return true;
		}
		break;
	}

	return false;
}

void Player::death() {

}



Enemy0::Enemy0(sf::Texture& texture, float x) {
	sprite.setTexture(texture);
	sprite.setScale(0.25f, 0.25f);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(x, 0);
	speed = 125;
	health = 25;
}

bool Enemy0::attack() {
	if (attack_clock.getElapsedTime().asSeconds() > 3) {
		attack_clock.restart();
		return true;
	}

	return false;
}



Enemy1::Enemy1(sf::Texture& texture, float x) {
	sprite.setTexture(texture);
	sprite.setScale(0.2f, 0.2f);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(x, 0);
	sprite.rotate(180);
	speed = 125;
	health = 40;
}

bool Enemy1::attack() {
	/*
	if (attack_clock.getElapsedTime().asSeconds() > 3) {
		attack_clock.restart();
		return true;
	}
	*/
	return false;
}



EnemyBoss::EnemyBoss(sf::Texture& texture, float x) {
	sprite.setTexture(texture);
	sprite.setScale(0.7f, 0.7f);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(x, 0);
	speed = 100;
	health = 100;
}

bool EnemyBoss::attack() {
	/*
	if (attack_clock.getElapsedTime().asSeconds() > 3) {
		attack_clock.restart();
		return true;
	}
	*/
	return false;
}