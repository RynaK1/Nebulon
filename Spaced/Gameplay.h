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
	sf::Font font;

	std::map<std::string, sf::Sound> sound;
	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Sprite> UIsprites;
	std::map<std::string, sf::Text> texts;

	Player player;
	std::vector<GameEntity*> player_bullets;
	std::vector<Enemy*> enemies;
	std::vector<GameEntity*> enemy_bullets;

	sf::FloatRect boundary;
	Stage stage;
	int money;
public:
	Gameplay(sf::RenderWindow* window);
	int display();
	void loadUI();
	void updateEntityPosition(float time);
	void updateEntityCollision();
	bool checkBossDNE();
	void startNextStage();
	void stageAnimation();
};