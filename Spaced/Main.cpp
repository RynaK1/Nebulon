#include <SFML\Graphics.hpp>
#include <iostream>

#include "Menu.h"
#include "Gameplay.h"
#include "End.h"
#include "Highscore.h"
#include "Externs.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 900), "Nebulon");

    Menu menu;
    Gameplay gameplay;
    End end;
    Highscore highscore;

    int go = GO_MENU;

    while (window.isOpen()) {

        switch (go) {
        case GO_MENU:
            cout << "Going to menu" << endl;
            go = menu.displayMainMenu(window);
            break;
        case GO_GAMEPLAY:
            cout << "Going to gameplay" << endl;
            go = gameplay.display(window);
            break;
        case GO_END:
            cout << "Going to end" << endl;
            go = end.display(window);
            break;
        case GO_HIGHSCORE:
            cout << "Going to highscore" << endl;
            go = highscore.display(window);
            break;
        case QUIT:
            window.close();
            break;
        }

    }

    return 0;
}