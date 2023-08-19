#include "Menu.h"
#include <iostream>

using namespace std;

int Menu::display(sf::RenderWindow &window) {
    //background
    sf::Texture bround;
    bround.loadFromFile("../sprites/spaceBackground.png");
    sf::Sprite background(bround);

    //buttons
    sf::Font font;
    font.loadFromFile("../sprites/AlfaSlabOne-Regular.ttf");

    sf::Text start_txt("Start", font);
    start_txt.setCharacterSize(30);
    start_txt.setStyle(sf::Text::Bold);
    start_txt.setFillColor(sf::Color::White);
    start_txt.setPosition(250, 500);



    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {

            case sf::Event::Closed:
                window.close();
                break;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (true) {

                }
            }

            window.clear();
            window.draw(background);
            window.draw(start_txt);
            window.display();
        }
    }
    return 1;
}