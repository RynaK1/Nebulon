#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Menu.h"
#include "Gameplay.h"
#include "End.h"
#include "Highscore.h"
#include "Externs.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Nebulon", sf::Style::Close);

    sf::Music title_theme;
    if (!title_theme.openFromFile("../Resources/Audio/title_theme.ogg")) {
        cerr << "Music file missing or improperly placed" << endl;
    }

    title_theme.play();

    Menu menu;
    Gameplay gameplay;
    End end;
    Highscore highscore;

    int go = GO_MENU;
    int main_volume = 100;

    while (window.isOpen()) {

        switch (go) {
        case GO_MENU:
            cout << "Going to menu" << endl;
            go = menu.displayMainMenu(window, title_theme, main_volume);
            break;
        case GO_GAMEPLAY:
            cout << "Going to gameplay" << endl;
            title_theme.stop();
            go = gameplay.display(window, title_theme);
            break;
        case GO_END:
            cout << "Going to end" << endl;
            go = end.display(window, title_theme);
            break;
        case GO_HIGHSCORE:
            cout << "Going to highscore" << endl;
            go = highscore.display(window, title_theme);
            break;
        case QUIT:
            window.close();
            break;
        }

    }

    return 0;
}