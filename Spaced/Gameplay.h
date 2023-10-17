#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>

#include "Player.h"
#include "Enemy.h"

class Gameplay {
private:
	sf::Font font;
	sf::Text money_txt;
	sf::Texture background_t;
	sf::Texture backgroundFHD_t;
	sf::Texture player_t;
	sf::Texture atk1_t;
	sf::Texture atk2_t;
	sf::Texture health_t;
	sf::Texture healthbar_t;
	sf::Texture moneyc_t;
	EnemyManager enemyManager;
	Player player;
	sf::Sprite background;
	sf::Sprite atk1;
	sf::Sprite atk2;
	sf::Sprite health;
	sf::Sprite healthbar;
	sf::Sprite moneyc;
	bool fhd;
	int money;
public:
	Gameplay();
	int display(sf::RenderWindow &window);
	std::array<bool, 4> checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size);
	std::array<bool, 2> updateCollisions(EnemyManager& em, Player& player);
	void scaleUI();
};