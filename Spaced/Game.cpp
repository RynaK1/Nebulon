#include "Game.h"

std::array<bool, 4> Game::checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size) {
	std::array<bool, 4> bounds = {true, true, true, true};

	if (pos.left <= 0) {
		bounds[0] = false;
	}
	if (pos.left + pos.width >= win_size.x) {
		bounds[1] = false;
	}
	if (pos.top <= 0) {
		bounds[2] = false;
	}
	if(pos.top + pos.height >= win_size.y) {
		bounds[3] = false;
	}

	return bounds;
}


std::array<bool, 2> Game::updateCollisions(EnemyManager& em, Player& player) { 
	std::array<bool, 2> death = {false, false};

	std::vector<Enemy> enemies = em.getEnemies();
	sf::Sprite player_s = player.getSprite();
	size_t enemies_size = enemies.size();
	for (int i = 0; i < enemies_size; i++) {
		if (enemies[i].getGlobalBounds().intersects(player_s.getGlobalBounds()))
		{
			int health = player.getHealth() - 10;
			if (health <= 0) {
				death[0] = true;
			}
			else {
				player.playerDamaged(10);
			}
		}
	}

	for (int i = 0; i < enemies.size(); i++) {
		std::vector<Bullet> bullets = player.getBullets();
		for (int j = 0; j < bullets.size(); j++) {
			if (bullets[j].getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
				int health = enemies[i].getHealth() - bullets[j].getDamage();
				if (health <= 0) {
					em.remove(i);
					death[1] = true;
				}
				else {
					em.setEnemyHealth(health, i);
				}
				player.removeBullet(j);
			}
		}
	}
	
	return death;
}