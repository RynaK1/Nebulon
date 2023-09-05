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
    string res = readFromFile("resolution");
    // set resolution data
    int window_x = stoi(res.substr(0, res.find('x')));
    int window_y = stoi(res.substr(res.find('x') + 1));

    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Nebulon", sf::Style::Close);

    // sounds
    sf::Music title_theme;
    if (!title_theme.openFromFile("../Resources/Audio/title_theme.ogg")) {
        cerr << "Title theme music file missing" << endl;
    }

    sf::Music sfx_interact;
    if (!sfx_interact.openFromFile("../Resources/Audio/laser.ogg")) {
        cerr << "SFX interact file missing" << endl;
    }

    sf::Vector2f sounds = calcVolTotal();
    title_theme.setVolume(sounds.x);
    title_theme.play();

    float svol = stof(readFromFile("sfx_volume"));
    sfx_interact.setVolume(sounds.y);

    Menu menu;
    Gameplay gameplay;
    End end;
    Highscore highscore;

    int go = GO_MAIN_MENU; //which screen to go to

    while (window.isOpen()) {

        switch (go) {
        case GO_MAIN_MENU:
            cout << "Going to main menu" << endl;
            go = menu.displayMainMenu(window, title_theme, sfx_interact);
            break;
        case GO_OPTIONS_MENU:
            cout << "Going to options menu" << endl;
            go = menu.displayOptions(window, title_theme, sfx_interact);
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