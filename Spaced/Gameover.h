#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Externs.h"

class Gameover {
private:
	bool fhd;
	sf::Sound sfx;
	sf::SoundBuffer sfx_buffer;
	sf::Music music;
	sf::Font font;
	sf::Texture background_t;
	sf::Texture backgroundFHD_t;
	sf::Sprite background;
public:
	Gameover();
	int display(sf::RenderWindow& window);
};