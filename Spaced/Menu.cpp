#include "Menu.h"

int Menu::displayMainMenu(sf::RenderWindow& window, sf::Music& music) {

    int win_x = window.getSize().x;
    int win_y = window.getSize().y;

    // ****************** graphic initializations ***********************
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    sf::Font font;
    font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf"); 

    sf::Text title_txt("Nebulon", font);
    title_txt.setCharacterSize(60);
    title_txt.setStyle(sf::Text::Bold);
    title_txt.setFillColor(sf::Color::White);
    title_txt.setPosition(((float)(win_x - title_txt.getLocalBounds().width) / 2), 
                            (float)((win_y - title_txt.getLocalBounds().height) / 3.5));

    sf::Text start_txt("Start", font);
    start_txt.setCharacterSize(30);
    start_txt.setStyle(sf::Text::Bold);
    start_txt.setFillColor(sf::Color::White);
    start_txt.setPosition((float)((win_x - start_txt.getLocalBounds().width) / 2),
                          (float)((win_y - start_txt.getLocalBounds().height) / 1.8));

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(30);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition((float)((win_x - options_txt.getLocalBounds().width) / 2),
                            (float)((win_y - options_txt.getLocalBounds().height) / 1.6));

    sf::Text highscores_txt("Highscores", font);
    highscores_txt.setCharacterSize(30);
    highscores_txt.setStyle(sf::Text::Bold);
    highscores_txt.setFillColor(sf::Color::White);
    highscores_txt.setPosition((float)((win_x - highscores_txt.getLocalBounds().width) / 2),
                               (float)((win_y - highscores_txt.getLocalBounds().height) / 1.44));

    sf::Text quit_txt("Quit", font);
    quit_txt.setCharacterSize(30);
    quit_txt.setStyle(sf::Text::Bold);
    quit_txt.setFillColor(sf::Color::White);
    quit_txt.setPosition((float)((win_x - quit_txt.getLocalBounds().width) / 2),
                         (float)((win_y - quit_txt.getLocalBounds().height) / 1.32));

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //highlight button if mouse is over button
            if (buttonBounds(mousePos, start_txt)) {
                start_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, options_txt)) {
                options_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, highscores_txt)) {
                highscores_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, quit_txt)) {
                quit_txt.setFillColor(sf::Color::Red);
            }
            else {
                start_txt.setFillColor(sf::Color::White);
                options_txt.setFillColor(sf::Color::White);
                highscores_txt.setFillColor(sf::Color::White);
                quit_txt.setFillColor(sf::Color::White);
            }

            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {
                if (buttonBounds(mousePos, start_txt)) {
                    return GO_GAMEPLAY;
                }
                else if (buttonBounds(mousePos, options_txt)) {
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, highscores_txt)) {
                    return GO_HIGHSCORE;
                }
                else if (buttonBounds(mousePos, quit_txt)) {
                    return QUIT;
                }
            }

            window.clear();
            window.draw(background);
            window.draw(start_txt);
            window.draw(options_txt);
            window.draw(highscores_txt);
            window.draw(title_txt);
            window.draw(quit_txt);
            window.display();
        }
    }

    std::cerr << "Error: displayMainMenu end of function return" << std::endl;
    return QUIT;
}


int Menu::displayOptions(sf::RenderWindow& window, sf::Music& music, int& volume) {

    // ****************** graphic initializations ***********************
    // background
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf"); 

    int win_x = window.getSize().x;
    int win_y = window.getSize().y;

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(45);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition((float)((win_x - options_txt.getLocalBounds().width) / 2),
                            (float)((win_y - options_txt.getLocalBounds().height) / 3.5));

    sf::Text volume_txt("Volume", font);
    volume_txt.setCharacterSize(30);
    volume_txt.setFillColor(sf::Color::White);
    volume_txt.setPosition((float)((win_x - volume_txt.getLocalBounds().width) / 2),
                           (float)((win_y - volume_txt.getLocalBounds().height) / 1.8));

    sf::RectangleShape vol_bar(sf::Vector2f(290, 6));
    vol_bar.setFillColor(sf::Color::White);
    vol_bar.setPosition((float)((win_x - vol_bar.getLocalBounds().width) / 2),
        (float)((win_y - vol_bar.getLocalBounds().height) / 1.6));
    
    sf::Text volume_num_txt("", font);
    std::string vol = std::to_string(volume);
    vol = vol.substr(0, vol.find('.'));
    volume_num_txt.setString(vol.append("%"));
    volume_num_txt.setCharacterSize(20);
    volume_num_txt.setFillColor(sf::Color::White);
    volume_num_txt.setPosition((float)(((win_x - vol_bar.getLocalBounds().width) / 2) + +vol_bar.getLocalBounds().width + 35),
                               (float)((win_y - volume_num_txt.getLocalBounds().height) / 1.61));

    sf::RectangleShape vol_knob(sf::Vector2f(10, 25));
    vol_knob.setOrigin(5, 13);
    vol_knob.setFillColor(sf::Color::Magenta);

    vol_knob.setPosition((float)((win_x - vol_bar.getLocalBounds().width) / 2) + (vol_bar.getLocalBounds().width * ((float)volume / 100.0)),
                         (float)((win_y - vol_bar.getLocalBounds().height) / 1.59));

    sf::Text bind_txt("Key Bindings", font);
    bind_txt.setCharacterSize(30);
    bind_txt.setFillColor(sf::Color::White);
    bind_txt.setPosition((float)((win_x - bind_txt.getLocalBounds().width) / 2),
                         (float)((win_y - bind_txt.getLocalBounds().height) / 1.44));

    sf::Text low_txt("1280x720", font);
    low_txt.setCharacterSize(30);
    low_txt.setFillColor(sf::Color::White);
    low_txt.setPosition((float)((win_x - low_txt.getLocalBounds().width) / 2.4),
        (float)((win_y - low_txt.getLocalBounds().height) / 1.32));

    sf::Text high_txt("1920x1080", font);
    high_txt.setCharacterSize(30);
    high_txt.setFillColor(sf::Color::White);
    high_txt.setPosition((float)((win_x - low_txt.getLocalBounds().width) / 1.72),
        (float)((win_y - high_txt.getLocalBounds().height) / 1.32));

    sf::Text back_txt("Back", font);
    back_txt.setCharacterSize(30);
    back_txt.setFillColor(sf::Color::White);
    back_txt.setPosition((float)((win_x - back_txt.getLocalBounds().width) / 2),
                         (float)((win_y - back_txt.getLocalBounds().height) / 1.22));


    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
                break;
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //highlight button if mouse is over button
            
            if (buttonBounds(mousePos, vol_knob)) {
                vol_knob.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, bind_txt)) {
                bind_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, back_txt)) {
                back_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, low_txt)) {
                low_txt.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, high_txt)) {
                high_txt.setFillColor(sf::Color::Red);
            }
            else {
                vol_knob.setFillColor(sf::Color::Magenta);
                bind_txt.setFillColor(sf::Color::White);
                back_txt.setFillColor(sf::Color::White);
                low_txt.setFillColor(sf::Color::White);
                high_txt.setFillColor(sf::Color::White);
            }

            //mouse tracker alternative for volume slider
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && buttonBounds(mousePos, vol_bar)) {

                float bar_length = vol_bar.getLocalBounds().width;
                if (mousePos.x > (win_x - bar_length) / 2 &&
                    mousePos.x < ((win_x - bar_length) / 2) + bar_length) {

                    vol_knob.setPosition((float)mousePos.x, (win_y - vol_bar.getLocalBounds().height) / (float)1.59);

                    volume = getVolumePercentage(mousePos.x, window.getSize().x);
                    music.setVolume((float)volume);
                    std::string vol = std::to_string(volume);
                    volume_num_txt.setString(vol.append("%"));
                }    
            }

            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {   
                if (buttonBounds(mousePos, bind_txt)) {
                    //key binds
                }
                else if (buttonBounds(mousePos, low_txt)) {
                    window.create(sf::VideoMode(1280, 720), "Nebulon", sf::Style::Close);
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, high_txt)) {
                    window.create(sf::VideoMode(1920, 1080), "Nebulon", sf::Style::Close);
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, back_txt)) {
                    return GO_MAIN_MENU;
                }
            }

            window.clear();
            window.draw(background);
            window.draw(options_txt);
            window.draw(volume_txt);
            window.draw(volume_num_txt);
            window.draw(vol_bar);
            window.draw(vol_knob);
            window.draw(bind_txt);
            window.draw(low_txt);
            window.draw(high_txt);
            window.draw(back_txt);
            window.display();
        }
    }

    std::cerr << "Error: displayOptionsMenu end of function return" << std::endl;
    return QUIT;
}