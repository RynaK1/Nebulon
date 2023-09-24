#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Menu.h"
#include "Gameplay.h"
#include "End.h"

using namespace std;

int main() {
    // window resolution
    string res = readFromFile("resolution");
    int window_x = stoi(res.substr(0, res.find('x')));
    int window_y = stoi(res.substr(res.find('x') + 1));

    sf::RenderWindow window(sf::VideoMode(window_x, window_y), "Nebulon", sf::Style::Close);
    if (window_x == 1920) {
        window.setPosition(sf::Vector2i(-8, -31)); //position correction for HD
    }

    // audios
    sf::Music music;
    if (!music.openFromFile("../Resources/Audio/theme_music.ogg")) {
        std::cerr << "Title theme music file missing" << std::endl;
    }
    sf::SoundBuffer sfx_buffer;
    if (!sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
        std::cerr << "sfx file missing" << std::endl;
    }
    sf::Sound sfx;
    sfx.setBuffer(sfx_buffer);

    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    sfx.setVolume(sounds.y);

    music.play();

    Menu menu;
    Gameplay gameplay;
    End end;


    int go = GO_MAIN_MENU; //which screen to go to

    while (window.isOpen()) {

        switch (go) {
        case GO_MAIN_MENU:
            cout << "Going to main menu" << endl;
            go = menu.displayMainMenu(window, music, sfx);
            break;
        case GO_OPTIONS_MENU:
            cout << "Going to options menu" << endl;
            go = menu.displayOptions(window, music, sfx);
            break;
        case GO_GAMEPLAY:
            cout << "Going to gameplay" << endl;
            music.stop();
            go = gameplay.display(window);
            break;
        case GO_END:
            cout << "Going to end" << endl;
            go = end.display(window, music);
            break;
        case QUIT:
            window.close();
            break;
        }
    }

    return 0;
}