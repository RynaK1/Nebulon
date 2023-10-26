#include "Gameover.h"


Gameover::Gameover() {

}


int Gameover::display(sf::RenderWindow& window) {
	// load textures

	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			if (evnt.type == sf::Event::Closed) {
				window.close();
			}
		}
	}

	return QUIT;
}