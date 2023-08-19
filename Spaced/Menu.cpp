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
    title_txt.setCharacterSize(55);
    title_txt.setStyle(sf::Text::Bold);
    title_txt.setFillColor(sf::Color::White);
    title_txt.setPosition(180, 250);

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

            switch (evnt.type) {

            case sf::Event::Closed:
                window.close();
                break;
            }
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //highlight button if mouse is over button
            if (buttonBounds(mousePos, 250, 340, 504, 530)) {
                start_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, 227, 363, 564, 590)) {
                options_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, 198, 392, 624, 650)) {
                highscores_txt.setFillColor(sf::Color::Red);
            }
            else {
                start_txt.setFillColor(sf::Color::White);
                options_txt.setFillColor(sf::Color::White);
                highscores_txt.setFillColor(sf::Color::White);
            }


            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (buttonBounds(mousePos, 250, 340, 505, 530)) {
                    return GO_GAMEPLAY;
                }
                else if (buttonBounds(mousePos, 227, 363, 564, 590)) {
                    displayOptions(window);
                }
                else if (buttonBounds(mousePos, 198, 392, 624, 650)) {
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
    return 1;
}

int Menu::displayOptions(sf::RenderWindow& window) {
    std::cout << "Going to options menu" << std::endl;

    while (window.isOpen()) {

    }

    return 1;
}