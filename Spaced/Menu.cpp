#include "Menu.h"
#include <iostream>

int Menu::displayMainMenu(sf::RenderWindow &window) {
    //background
    sf::Texture bround;
    bround.loadFromFile("../sprites/spaceBackground.png");
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../sprites/AlfaSlabOne-Regular.ttf"); \

    sf::Text title_txt("Nebulon", font);
    title_txt.setCharacterSize(60);
    title_txt.setStyle(sf::Text::Bold);
    title_txt.setFillColor(sf::Color::White);
    title_txt.setPosition(160, 250);

    sf::Text start_txt("Start", font);
    start_txt.setCharacterSize(30);
    start_txt.setStyle(sf::Text::Bold);
    start_txt.setFillColor(sf::Color::White);
    start_txt.setPosition(250, 500);

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(30);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition(227, 560);

    sf::Text highscores_txt("Highscores", font);
    highscores_txt.setCharacterSize(30);
    highscores_txt.setStyle(sf::Text::Bold);
    highscores_txt.setFillColor(sf::Color::White);
    highscores_txt.setPosition(198, 620);


    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //highlight button if mouse is over button
            if (buttonBounds(mousePos, 250, 340, 504, 530)) {
                start_txt.setFillColor(sf::Color::Magenta);
            }
            else if (buttonBounds(mousePos, 227, 363, 564, 590)) {
                options_txt.setFillColor(sf::Color::Magenta);
            }
            else if (buttonBounds(mousePos, 198, 392, 624, 650)) {
                highscores_txt.setFillColor(sf::Color::Magenta);
            }
            else {
                start_txt.setFillColor(sf::Color::White);
                options_txt.setFillColor(sf::Color::White);
                highscores_txt.setFillColor(sf::Color::White);
            }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (buttonBounds(mousePos, 250, 340, 505, 530)) {
                    start_txt.setFillColor(sf::Color::Red);
                    window.draw(start_txt);
                    window.display();
                    return GO_GAMEPLAY;
                }
                else if (buttonBounds(mousePos, 227, 363, 564, 590)) {
                    options_txt.setFillColor(sf::Color::Red);
                    window.draw(options_txt);
                    window.display();
                    displayOptions(window);
                }
                else if (buttonBounds(mousePos, 198, 392, 624, 650)) {
                    highscores_txt.setFillColor(sf::Color::Red);
                    window.draw(highscores_txt);
                    window.display();
                    return GO_HIGHSCORE;
                }
            }

            window.clear();
            window.draw(background);
            window.draw(start_txt);
            window.draw(options_txt);
            window.draw(highscores_txt);
            window.draw(title_txt);
            window.display();
        }
    }
    return -1;
}

int Menu::displayOptions(sf::RenderWindow& window) {
    sf::Texture bround;
    bround.loadFromFile("../sprites/spaceBackground.png");
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../sprites/AlfaSlabOne-Regular.ttf"); \

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(45);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition(200, 260);

    sf::Text volume_txt("Volume", font);
    volume_txt.setCharacterSize(25);
    //volume_txt.setStyle(sf::Text::Bold);
    volume_txt.setFillColor(sf::Color::White);
    volume_txt.setPosition(240, 480);

    sf::RectangleShape vol_bar(sf::Vector2f(290, 6));
    vol_bar.setFillColor(sf::Color::White);
    vol_bar.setPosition(150, 515);

    sf::RectangleShape vol_knob(sf::Vector2f(10, 25));
    vol_knob.setFillColor(sf::Color::Green);
    vol_knob.setPosition(430, 505);

    int knob_pos = 430;

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
                break;
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //highlight button if mouse is over button
            if (buttonBounds(mousePos, knob_pos, knob_pos + 10, 505, 530)) {
                vol_knob.setFillColor(sf::Color::Magenta);
            }
            else {
                vol_knob.setFillColor(sf::Color::Green);
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (buttonBounds(mousePos, 150, 440, 505, 530)) {
                    vol_knob.setFillColor(sf::Color::Red);
                    vol_knob.setPosition(mousePos.x - 5, 505);
                    knob_pos = mousePos.x - 5;

                    window.draw(vol_knob);
                    window.display();
                }
            }

            window.clear();
            window.draw(background);
            window.draw(options_txt);
            window.draw(volume_txt);
            window.draw(vol_bar);
            window.draw(vol_knob);
            window.display();
        }
    }

    return -1;
}