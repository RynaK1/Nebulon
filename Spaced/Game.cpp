#include "Game.h"

std::array<bool, 4> Game::checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size) {
	float scale = 1.5;
	if (win_size.x == 1920) {
		scale = 2.25;
	}

	std::array<bool, 4> bounds = {true, true, true, true};

	if (pos.left <= 0) {
		bounds[0] = false;
	}
	if (pos.left + (31 * scale) >= win_size.x) {
		bounds[1] = false;
	}
	if (pos.top <= 0) {
		bounds[2] = false;
	}
	if(pos.top + (27 * scale) >= win_size.y) {
		bounds[3] = false;
	}

	return bounds;
}


void Game::updateCollisions(EnemyManager& em, Player& player) {
	std::vector<Enemy> enemies = em.getEnemies();

	for (int i = 0; i < enemies.size(); i++) {
		std::vector<Bullet> bullets = player.getBullets();
		for (int j = 0; j < bullets.size(); j++) {
			if (bullets[j].getGlobalBounds().intersects(enemies[i].getSprite().getGlobalBounds())) {
				em.setEnemyHealth(enemies[i].getHealth() - bullets[j].getDamage(), i);
				player.removeBullet(j);
			}
		}
	}

	sf::Sprite player_s = player.getSprite();
	size_t enemies_size = enemies.size();
	for (int i = 0; i < enemies_size; i++) {
		if (enemies[i].getSprite().getGlobalBounds().intersects(player_s.getGlobalBounds())) {
			player.playerDamaged(10);
		}
	}
}