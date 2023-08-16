#include <SFML\Graphics.hpp>
#include <iostream>
#include "Menu.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 600), "Nebulon");

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {

            case sf::Event::Closed:
                window.close();
                break;

            }
        }
    }

    return 0;
}