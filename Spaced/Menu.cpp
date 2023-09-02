#include "Menu.h"

int Menu::displayMainMenu(sf::RenderWindow& window, sf::Music& music) {

    float win_x = (float)window.getSize().x;
    float win_y = (float)window.getSize().y;

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
    title_txt.setPosition(((win_x - title_txt.getLocalBounds().width) / 2.0f), 
                           (win_y - title_txt.getLocalBounds().height) / 3.5f);

    sf::Text start_txt("Start", font);
    start_txt.setCharacterSize(30);
    start_txt.setStyle(sf::Text::Bold);
    start_txt.setFillColor(sf::Color::White);
    start_txt.setPosition(((win_x - start_txt.getLocalBounds().width) / 2.0f),
                           (win_y - start_txt.getLocalBounds().height) / 1.8f);

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(30);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition(((win_x - options_txt.getLocalBounds().width) / 2.0f),
                             (win_y - options_txt.getLocalBounds().height) / 1.6f);

    sf::Text highscores_txt("Highscores", font);
    highscores_txt.setCharacterSize(30);
    highscores_txt.setStyle(sf::Text::Bold);
    highscores_txt.setFillColor(sf::Color::White);
    highscores_txt.setPosition(((win_x - highscores_txt.getLocalBounds().width) / 2.0f),
                                (win_y - highscores_txt.getLocalBounds().height) / 1.44f);

    sf::Text quit_txt("Quit", font);
    quit_txt.setCharacterSize(30);
    quit_txt.setStyle(sf::Text::Bold);
    quit_txt.setFillColor(sf::Color::White);
    quit_txt.setPosition(((win_x - quit_txt.getLocalBounds().width) / 2.0f),
                          (win_y - quit_txt.getLocalBounds().height) / 1.32f);


    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            // highlight button if mouse is over button
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

            // button actions
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



int Menu::displayOptions(sf::RenderWindow& window, sf::Music& music) { 

    // ****************** graphic initializations ***********************
    // background
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf"); 

    float win_x = (float)window.getSize().x;
    float win_y = (float)window.getSize().y;

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(45);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition(((win_x - options_txt.getLocalBounds().width) / 2),
                             (win_y - options_txt.getLocalBounds().height) / 3.5f);

    sf::Text mvol_txt("Main Volume", font);
    mvol_txt.setCharacterSize(25);
    mvol_txt.setFillColor(sf::Color::White);
    mvol_txt.setPosition(((win_x - mvol_txt.getLocalBounds().width) / 2),
                          (win_y - mvol_txt.getLocalBounds().height) / 2.1f);

    sf::RectangleShape mvol_bar(sf::Vector2f(230, 6));
    mvol_bar.setFillColor(sf::Color::White);
    mvol_bar.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2),
                          (win_y - mvol_bar.getLocalBounds().height) / 1.9f);
    
    float mvol_num = stof(readFromFile("main_volume"));
    sf::Text mvol_num_txt(std::to_string(mvol_num), font);
    mvol_num_txt.setString(getVolPercentString(mvol_num));
    mvol_num_txt.setCharacterSize(20);
    mvol_num_txt.setFillColor(sf::Color::White);
    mvol_num_txt.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2) + mvol_bar.getLocalBounds().width + 35,
                              (win_y - mvol_num_txt.getLocalBounds().height) / 1.91f);

    sf::RectangleShape mvol_knob(sf::Vector2f(10, 25));
    mvol_knob.setOrigin(5, 13);
    mvol_knob.setFillColor(sf::Color::Magenta);

    mvol_knob.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2) + (mvol_bar.getLocalBounds().width * ((float)mvol_num / 100)),
                           (win_y - mvol_bar.getLocalBounds().height) / 1.89f);

    //sf::Text 

    sf::Text bind_txt("Key Bindings", font);
    bind_txt.setCharacterSize(30);
    bind_txt.setFillColor(sf::Color::White);
    bind_txt.setPosition(((win_x - bind_txt.getLocalBounds().width) / 2),
                          (win_y - bind_txt.getLocalBounds().height) / 1.44f);

    sf::Text low_txt("1280x720", font);
    low_txt.setCharacterSize(28);
    low_txt.setFillColor(sf::Color::White);
    low_txt.setPosition(((win_x - low_txt.getLocalBounds().width) / 2.4f),
                         (win_y - low_txt.getLocalBounds().height) / 1.32f);

    sf::Text high_txt("1920x1080", font);
    high_txt.setCharacterSize(28);
    high_txt.setFillColor(sf::Color::White);
    high_txt.setPosition(((win_x - low_txt.getLocalBounds().width) / 1.72f),
                          (win_y - high_txt.getLocalBounds().height) / 1.32f);

    sf::Text back_txt("Back", font);
    back_txt.setCharacterSize(30);
    back_txt.setFillColor(sf::Color::White);
    back_txt.setPosition(((win_x - back_txt.getLocalBounds().width) / 2),
                          (win_y - back_txt.getLocalBounds().height) / 1.22f);


    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
                break;
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            //highlight button if mouse is over button   
            if (buttonBounds(mousePos, mvol_knob)) {
                mvol_knob.setFillColor(sf::Color::Red);
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
                mvol_knob.setFillColor(sf::Color::Magenta);
                bind_txt.setFillColor(sf::Color::White);
                back_txt.setFillColor(sf::Color::White);
                low_txt.setFillColor(sf::Color::White);
                high_txt.setFillColor(sf::Color::White);
            }

            //mouse tracker alternative for volume slider
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (buttonBounds(mousePos, mvol_bar)) {
                    mvol_knob.setPosition((float)mousePos.x, (win_y - mvol_bar.getLocalBounds().height) / 1.89f);

                    mvol_num = calcVolPercent((float)mousePos.x, mvol_bar.getPosition().x);
                    music.setVolume(mvol_num);
                    mvol_num_txt.setString(getVolPercentString(mvol_num));
                    writeToFile(std::to_string(mvol_num), "main_volume");
                } 
            }

            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {   
                if (buttonBounds(mousePos, bind_txt)) {
                    //key binds
                }
                else if (buttonBounds(mousePos, low_txt)) {
                    window.create(sf::VideoMode(1280, 720), "Nebulon", sf::Style::Close);
                    writeToFile("1280x720", "resolution");
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, high_txt)) {
                    window.create(sf::VideoMode(1920, 1080), "Nebulon", sf::Style::Close);
                    writeToFile("1920x1080", "resolution");
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, back_txt)) {
                    return GO_MAIN_MENU;
                }
            }

            window.clear();
            window.draw(background);
            window.draw(options_txt);
            window.draw(mvol_txt);
            window.draw(mvol_num_txt);
            window.draw(mvol_bar);
            window.draw(mvol_knob);
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