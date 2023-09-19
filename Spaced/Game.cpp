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


bool Game::checkPlayerCollision(Player player, EnemyManager em) { //enemy attack
	std::vector<Enemy> enemies = em.getEnemies();
	sf::Sprite player_s = player.getSprite();
	int em_size = em.getEnemies_size();
	for (int i = 0; i < em_size; i++) {
		if (enemies[i].getSprite().getGlobalBounds().intersects(player_s.getGlobalBounds())) {
			return true;
		}
	}

	return false;
}


bool Game::checkEnemyCollision(Enemy e, BulletManager bm) {
	std::vector<sf::Sprite> bullets = bm.getBullets();

	int bullets_size = bullets.size();
	for (int i = 0; i < bullets_size; i++) {
		if (bullets[i].getGlobalBounds().intersects(e.getSprite().getGlobalBounds())) {
			return true;
		}
	}
	return false;
}
