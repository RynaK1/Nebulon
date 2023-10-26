#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include "Externs.h"

class End {
private:
	sf::Music music;
	sf::SoundBuffer sfx_buffer;
	sf::Sound sfx;
	sf::Font font;
	sf::Texture background_t;
	sf::Texture backgroundFHD_t;
	sf::Sprite background;
	bool fhd;
	int money;
public:
	End();
	int display(sf::RenderWindow& window);
};