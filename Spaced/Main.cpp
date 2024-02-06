#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Menu.h"
#include "Gameplay.h"
#include "Gameover.h"
#include "End.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Nebulon");
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        window.setSize(sf::Vector2u(1920, 1080));
        window.setPosition(sf::Vector2i(-8, -31)); //position correction for HD
    }

    int go = GO_MAIN_MENU; //which screen to go to
    while (window.isOpen()) {
        switch (go) {
        case GO_MAIN_MENU: {
            Menu menu(&window);
            cout << "Going to main menu" << endl;
            go = menu.displayMain();
            break;
        }
        case GO_GAMEPLAY: {
            Gameplay gameplay(&window);
            cout << "Going to gameplay" << endl;
            go = gameplay.display();
            break;
        }
        case GO_END: {
            End end;
            cout << "Going to end" << endl;
            go = end.display(window);
            break;
        }
        case GO_GAMEOVER: {
            Gameover gameover;
            cout << "Going to gameover" << std::endl;
            go = gameover.display(window);
            break;
        }
        case QUIT:
            window.close();
            break;
        }
    }

    return 0;
}