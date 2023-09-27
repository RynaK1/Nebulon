#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Externs.h"
#include "BackEntityManager.h"


class Menu {
private:
	sf::Texture background_t;
	sf::Sprite background;
	sf::Texture backEntities_t[10];
	sf::Music music;
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	BackEntityManager backEntityManager;
public:
	Menu();
	int displayMainMenu(sf::RenderWindow& window);
	int displayOptions(sf::RenderWindow& window);
	void resolutionReset(bool fhd);
};