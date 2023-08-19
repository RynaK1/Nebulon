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

    int go = go_menu;

    while (window.isOpen()) {

        switch (go) {
        case go_menu:
            cout << "Going to menu" << endl;
            go = menu.display(window);
            break;
        case go_gameplay:
            cout << "Going to gameplay" << endl;
            go = gameplay.display(window);
            break;
        case go_end:
            cout << "Going to end" << endl;
            go = end.display(window);
            break;
        case go_highscore:
            cout << "Going to highscore" << endl;
            go = highscore.display(window);
            break;
        default:
            window.close();
            break;
        }

    }

    return 0;
}