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



Entity::Entity(sf::Texture& texture, float start_pos, float speed) {
	sprite.setTexture(texture);
	sf::FloatRect size = sprite.getGlobalBounds();
	sprite.setOrigin(size.width / 2, size.height / 2);
	sprite.setPosition(start_pos, 0);
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
		x -= speed * eqs[0].speed_mult * time;
	}
	else {
		x += speed * eqs[0].speed_mult * time;
	}

	if ((!eqs[0].isNegative && x >= eqs[0].x_max) ||
		(eqs[0].isNegative && x <= eqs[0].x_max)) {
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



void GameEntity::setHealth(int health) {
	this->health = health;
}

void GameEntity::setDmg(int dmg) {
	this->dmg = dmg;
}

int GameEntity::getHealth() {
	return health;
}

int GameEntity::getDmg() {
	return dmg;
}



Player::Player(sf::Texture& texture, sf::Vector2f start_pos, float speed, int health) {
	sprite.setTexture(texture);
	sprite.setPosition(start_pos.x, start_pos.y);
	sprite.setScale(0.25f, 0.25f);
	this->speed = speed;
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

void Player::hit(int dmg) {
	if (hit_clock.getElapsedTime().asSeconds() >= 1) {
		this->health -= dmg;
		hit_clock.restart();
	}
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

void Player::attack(std::map<std::string, sf::Texture>& textures, std::vector<GameEntity*>* player_bullets) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		if (attack1_clock.getElapsedTime().asSeconds() >= 1) {
			attack1_clock.restart();

			sf::FloatRect pos = this->getGlobalBounds();
			GameEntity* attack1 = new GameEntity(textures["bullet0"], pos.left + (pos.width / 2), 10, 1, 10);
			attack1->setScale(3, 3);
			std::vector<Equation> attack1Eq;
			attack1Eq.push_back(Equation(1, -(pos.left + (pos.width / 2)), -pos.top, 1, 99, 3000, 1, false));
			attack1->setEqs(attack1Eq);
			player_bullets->push_back(attack1);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		if (attack2_clock.getElapsedTime().asSeconds() >= 2.5) {
			attack2_clock.restart();

			sf::FloatRect pos = this->getGlobalBounds();
			GameEntity* attack2 = new GameEntity(textures["bullet1"], pos.left + (pos.width / 2), 6, 1, 25);
			attack2->setScale(4, 4);
			std::vector<Equation> attack2Eq;
			attack2Eq.push_back(Equation(1, -(pos.left + (pos.width / 2)), -pos.top, 1, 99, 3000, 1, false));
			attack2->setEqs(attack2Eq);
			player_bullets->push_back(attack2);
		}
	}
}

void Player::death() {

}



bool Enemy::getIsBoss() {
	return isBoss;
}

void Enemy::hit(int dmg) {
	if (hit_clock.getElapsedTime().asSeconds() >= 1) {
		this->health -= dmg;
		hit_clock.restart();
	}
}

void Enemy::attack(std::map<std::string, sf::Texture>& textures, std::vector<GameEntity*>* enemy_bullets) {
	switch (attackType) {
	case 0: case 100:
		if (attack_clock.getElapsedTime().asSeconds() >= 2) {
			attack_clock.restart();

			sf::FloatRect pos = this->getGlobalBounds();
			GameEntity* attack = new GameEntity(textures["bullet0"], pos.left + (pos.width / 2), 7, 1, 15);
			attack->setRotation(180);
			attack->setScale(3, 3);
			std::vector<Equation> attackEq;
			attackEq.push_back(Equation(1, -(pos.left + (pos.width / 2)), -(pos.top + (pos.height / 2)), 1, 99, -1000, 1, true));
			attack->setEqs(attackEq);
			enemy_bullets->push_back(attack);
		}
		break;
	default:
		break;
	}
}