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
	sf::Texture transparent_t;
	sf::Texture backgroundFHD_t;
	sf::Texture transparentFHD_t;
	sf::Sprite background;
	sf::Sprite transparent;
	sf::Texture movingEntities_t[10];
	MovingEntityManager movingEntityManager;
	sf::Music music;
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	float win_x;
	float win_y;
public:
	Menu();
	int displayMain(sf::RenderWindow& window);
	int displayOptions(sf::RenderWindow& window);
	void resolutionReset(sf::Texture* movingEntities_t, bool fhd);
};