#include "Gameover.h"


Gameover::Gameover() {
	//audio
	if (!music.openFromFile("../Resources/Audio/theme_music.ogg")) {
		std::cerr << "Could not load theme_music.ogg" << std::endl;
	}
	if (!sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
		std::cerr << "Could not load sfx_laser.ogg" << std::endl;
	}
	sfx.setBuffer(sfx_buffer);

	fhd = false;
	if (!background_t.loadFromFile("../Resources/Textures/BackgroundGame.png") ||
		!backgroundFHD_t.loadFromFile("../Resources/Textures/BackgroundGame_FHD.png")) {
		std::cerr << "BackgroundGame(_FHD).png file missing" << std::endl;
	}

	if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
		std::cerr << "Could not load font" << std::endl;
	}
}


int Gameover::display(sf::RenderWindow& window) {
	sf::Vector2f sounds = calcVolTotal();
	music.setVolume(sounds.x);
	sfx.setVolume(sounds.y);

	fhd = false;
	if (readFromFile("resolution").compare("1920x1080") == 0) {
		fhd = true;
	}

	//background
	background.setTexture(background_t);
	if (fhd) {
		background = sf::Sprite();
		background.setTexture(backgroundFHD_t);
	}

	int win_x = 1280;
	int win_y = 720;
	if (fhd) {
		win_x = 1920;
		win_y = 1080;
	}

	sf::Text gameover_txt("All drones destroyed", font);
	gameover_txt.setCharacterSize(45);
	gameover_txt.setStyle(sf::Text::Bold);
	gameover_txt.setFillColor(sf::Color::White);
	gameover_txt.setPosition(((win_x - gameover_txt.getLocalBounds().width) / 2),
		(win_y - gameover_txt.getLocalBounds().height) / 2.5f);

	sf::Text back_txt("Back", font);
	back_txt.setCharacterSize(30);
	back_txt.setStyle(sf::Text::Bold);
	back_txt.setFillColor(sf::Color::White);
	back_txt.setPosition(((win_x - back_txt.getLocalBounds().width) / 2),
		(win_y - back_txt.getLocalBounds().height) / 1.8f);

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}

			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			// highlight button if mouse is over button
			if (buttonBounds(window.mapPixelToCoords(mousePos), back_txt)) {
				back_txt.setFillColor(sf::Color::Red);
			}
			else {
				back_txt.setFillColor(sf::Color::White);
			}

			// button actions
			if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {
				if (buttonBounds(window.mapPixelToCoords(mousePos), back_txt)) {
					sfx.play();
					return GO_MAIN_MENU;
				}
			}
		}
		window.clear();
		window.draw(background);
		window.draw(gameover_txt);
		window.draw(back_txt);
		window.display();
	}

	return QUIT;
}