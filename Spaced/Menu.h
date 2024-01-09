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
	sf::RenderWindow* window;
	sf::Clock frame_clock;
	sf::Music music;
	sf::Sound sfx;
	sf::SoundBuffer sfx_buffer;
	sf::Font font;
	std::map<std::string, sf::Texture> textures;
	sf::Sprite background;
	sf::Sprite transparent;

	sf::Clock em_clock;
	bool em_flags[3];
	EntityManager em_back;
	EntityManager em_front;

	std::map<std::string, sf::Text> UI_main;
	std::map<std::string, sf::Text> UI_options;
	std::map<std::string, sf::RectangleShape> UI_options2;
	bool fhd;
	int win_x;
	int win_y;

	std::vector<Entity> entities;
public:
	Menu(sf::RenderWindow* window);
	int displayMain();
	int displayOptions();
	void resolutionReset(bool fhd);
	void loadUIMain();
	void loadUIOptions();
	void loadEntities();
	void highlightMain(sf::Vector2i mousePos);
	void highlightOptions(sf::Vector2i mousePos);
	int buttonPressedMain(sf::Vector2i mousePos);
	int buttonPressedOptions(sf::Vector2i mousePos);
	void updateEntities();
	void changeEntityFHD();
};