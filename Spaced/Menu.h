#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Externs.h"
#include "Entity.h"


class Menu {
private:
	sf::Texture background_t;
	sf::Texture backgroundFHD_t;
	sf::Sprite background;
	sf::Texture movingEntities_t[10];
	MovingEntityManager movingEntityManager;
	sf::Music music;
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
public:
	Menu();
	int displayMainMenu(sf::RenderWindow& window);
	int displayOptions(sf::RenderWindow& window);
	void resolutionReset(bool fhd);
};