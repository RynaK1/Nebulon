#include "End.h"

End::End() {
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

	money = stoi(readFromFile("money"));
}


int End::display(sf::RenderWindow &window) {
	sf::Vector2f sounds = calcVolTotal();
	music.setVolume(sounds.x);
	sfx.setVolume(sounds.y);

	fhd = false;
	if (readFromFile("resolution").compare("1920x1080") == 0) {
		fhd = true;
	}

	int win_x = 1280;
	int win_y = 720;
	if (fhd) {
		win_x = 1920;
		win_y = 1080;
	}

	//background
	background.setTexture(background_t);
	if (fhd) {
		background = sf::Sprite();
		background.setTexture(backgroundFHD_t);
	}

	//texts and buttons
	sf::Text lives_txt("Drones left: " + readFromFile("lives"), font);
	lives_txt.setCharacterSize(30);
	lives_txt.setStyle(sf::Text::Bold);
	lives_txt.setFillColor(sf::Color::White);
	lives_txt.setPosition(((win_x - lives_txt.getLocalBounds().width) / 2),
		(win_y - lives_txt.getLocalBounds().height) / 3);

	sf::Text money_txt("Money: " + readFromFile("money"), font);
	money_txt.setCharacterSize(30);
	money_txt.setStyle(sf::Text::Bold);
	money_txt.setFillColor(sf::Color::White);
	money_txt.setPosition(((win_x - money_txt.getLocalBounds().width) / 2),
		(win_y - money_txt.getLocalBounds().height) / 2.5f);

	sf::Text gained_txt("Gained: " + std::to_string(stoi(readFromFile("money")) - money), font);
	gained_txt.setCharacterSize(30);
	gained_txt.setStyle(sf::Text::Bold);
	gained_txt.setFillColor(sf::Color::White);
	gained_txt.setPosition(((win_x - gained_txt.getLocalBounds().width) / 2),
		(win_y - gained_txt.getLocalBounds().height) / 2.2f);

	sf::Text back_txt("Back", font);
	back_txt.setCharacterSize(30);
	back_txt.setStyle(sf::Text::Bold);
	back_txt.setFillColor(sf::Color::White);
	back_txt.setPosition(((win_x - back_txt.getLocalBounds().width) / 2),
		(win_y - back_txt.getLocalBounds().height) / 1.8f);

	//update money and lives
	money = stoi(readFromFile("money"));


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
			if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left) {
				if (buttonBounds(window.mapPixelToCoords(mousePos), back_txt)) {
					sfx.play();
					return GO_MAIN_MENU;
				}
			}
		}

		window.clear();

		window.draw(background);
		window.draw(lives_txt);
		window.draw(money_txt);
		window.draw(gained_txt);
		window.draw(back_txt);
		window.display();
	}

	return QUIT;
}