#include "Highscore.h"

int Highscore::display(sf::RenderWindow& window, sf::Music& music) {
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf"); 

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

        }

        window.clear();
        window.display();
    }

    return 1;
}