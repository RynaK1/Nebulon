#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

#include "Menu.h"
#include "Gameplay.h"
#include "BackEntityManager.h"
#include "End.h"

using namespace std;

int main() {
    // window resolution
    string res = readFromFile("resolution");
    int win_x = stoi(res.substr(0, res.find('x')));
    int win_y = stoi(res.substr(res.find('x') + 1));

    sf::RenderWindow window(sf::VideoMode(win_x, win_y), "Nebulon", sf::Style::Close);
    if (win_x == 1920) {
        window.setPosition(sf::Vector2i(-8, -31)); //position correction for HD
    }

    Menu menu;
    Gameplay gameplay;
    End end;

    int go = GO_MAIN_MENU; //which screen to go to

    while (window.isOpen()) {

        switch (go) {
        case GO_MAIN_MENU:
            cout << "Going to main menu" << endl;
            go = menu.displayMainMenu(window);
            break;
        case GO_OPTIONS_MENU:
            cout << "Going to options menu" << endl;
            go = menu.displayOptions(window);
            break;
        case GO_GAMEPLAY:
            cout << "Going to gameplay" << endl;
            go = gameplay.display(window);
            break;
        case GO_END:
            cout << "Going to end" << endl;
            go = end.display(window);
            break;
        case QUIT:
            window.close();
            break;
        }
    }

    return 0;
}