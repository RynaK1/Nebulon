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
	sf::Clock frame_clock;
	sf::RenderWindow* window;
	sf::Music music;
	sf::Sound sfx;
	sf::SoundBuffer sfx_buffer;
	sf::Font font;
	sf::Texture background_t;
	sf::Texture transparent_t;
	sf::Texture backgroundFHD_t;
	sf::Texture transparentFHD_t;
	sf::Texture movingEntities_t[7];
	sf::Sprite background;
	sf::Sprite transparent;

	sf::Clock mem_clock;
	bool mem_flags[2];
	MovingEntityManager mem_back;
	MovingEntityManager mem_front;

	std::map<std::string, sf::Text> UI_main;
	std::map<std::string, sf::Text> UI_options;
	std::map<std::string, sf::RectangleShape> UI_options2;
	bool fhd;
	int win_x;
	int win_y;
public:
	Menu(sf::RenderWindow* window);
	int displayMain();
	int displayOptions();
	void resolutionReset(sf::Texture* movingEntities_t, bool fhd);
	void loadUIMain(bool fhd);
	void loadUIOptions(bool fhd);
	void highlightMain(sf::Vector2i mousePos);
	void highlightOptions(sf::Vector2i mousePos);
	int buttonPressedMain(sf::Vector2i mousePos);
	int buttonPressedOptions(sf::Vector2i mousePos);
	void updateMovingEntities();
};