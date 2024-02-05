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
	sf::Font font;
	sf::Sound sfx;
	sf::SoundBuffer sfx_buffer;
	sf::Music music;

	std::map<std::string, sf::Texture> textures;
	std::map<std::string, sf::Sprite> UIsprites;
	std::map<std::string, sf::Text> UI_main;
	std::map<std::string, sf::Text> UI_options;
	std::map<std::string, sf::RectangleShape> UI_options2;

	std::vector<Entity> entities_front;
	std::vector<Entity> entities_back;

	sf::Clock entities_clock;
	bool entities_flags[3];

	int win_x;
	int win_y;
public:
	Menu(sf::RenderWindow* window);
	int displayMain();
	int displayOptions();
	void loadUIMain();
	void loadUIOptions();
	void highlightButtonMain(sf::Vector2i mousePos);
	void highlightButtonOptions(sf::Vector2i mousePos);
	int buttonPressedMain(sf::Vector2i mousePos);
	int buttonPressedOptions(sf::Vector2i mousePos);
	void spawnEntities();
	void updateEntityPosition();
	void volumeSliderOptions(sf::Vector2i mousePos);
};