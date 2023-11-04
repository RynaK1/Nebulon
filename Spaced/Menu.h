#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Externs.h"
#include "Entity.h"

class Menu {
private:
	sf::Clock clock;
	float time{};
	sf::Font font;
	sf::Texture background_t;
	sf::Texture transparent_t;
	sf::Texture backgroundFHD_t;
	sf::Texture transparentFHD_t;
	sf::Sprite background;
	sf::Sprite transparent;
	sf::Texture movingEntities_t[7];
	MovingEntityManager movingEntityManager;
	sf::Music music;
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	std::map<std::string, sf::Text> UI_main;
	std::map<std::string, sf::Text> UI_options;
	std::map<std::string, sf::RectangleShape> UI_options2;
	bool fhd;
public:
	Menu();
	int displayMain(sf::RenderWindow& window);
	int displayOptions(sf::RenderWindow& window);
	void resolutionReset(sf::Texture* movingEntities_t, bool fhd);
	void loadUIMain(bool fhd);
	void loadUIOptions(bool fhd);
};