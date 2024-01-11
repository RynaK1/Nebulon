#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <typeinfo>

#include "Externs.h"
#include "Entity.h"
#include "Stage.h"

class Gameplay {
private:
	sf::RenderWindow* window;
	sf::Clock frame_clock;
	sf::Clock animation_clock;
	sf::Music music;
	sf::SoundBuffer sfx_bullet_bfr;
	sf::Sound sfx_bullet;
	sf::SoundBuffer sfx_enemy_death_bfr;
	sf::Sound sfx_enemy_death;
	sf::Font font;
	sf::Text money_txt;
	sf::Text stage_txt;
	std::map<std::string, sf::Texture> textures;
	sf::Sprite background;
	sf::Sprite bullet1_UI;
	sf::Sprite bullet2_UI;
	sf::Sprite health_UI;
	sf::Sprite healthbar_UI;
	sf::Sprite money_UI;
	Player player;
	bool fhd;
	bool bossDeath;
	int money;
	int stage_num;
	bool animation_flag;
	sf::FloatRect boundary;
public:
	Gameplay(sf::RenderWindow* window);
	int display();
	//std::array<bool, 2> updateCollisions(EnemyManager& em, Player& player);
	void scaleUI();
	void scaleEntities();
	void stageAnimation();
};

// IMPLEMENT STAGE SYSTEM THEN COLLISION