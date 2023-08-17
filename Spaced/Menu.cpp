#include "Menu.h"
#include <iostream>

using namespace std;

int Menu::display(sf::RenderWindow &window) {

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {

            case sf::Event::Closed:
                window.close();
                break;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                cout << "test" << endl;
            }

            //window.clear();
            //window.display();
        }
    }
    return 1;
}