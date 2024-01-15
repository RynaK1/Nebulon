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

	std::vector<Enemy*> enemies;
	//std::vector<>
	//std::vector<>

	sf::FloatRect boundary;
	Player player;
	Stage stage;
	int money;

	bool fhd;
public:
	Gameplay(sf::RenderWindow* window);
	int display();
	void updateCollisions();
	void scaleUI();
	void scaleEntities();
	void updateEntityPosition(float time);
	void stageAnimation();
};