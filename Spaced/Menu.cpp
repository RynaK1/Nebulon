#include "Menu.h"

int Menu::displayMainMenu(sf::RenderWindow& window, sf::Music& music, sf::Sound& sfx) {
    //set clock
    sf::Clock clock;
    float time{};

    float win_x = (float)window.getSize().x;
    float win_y = (float)window.getSize().y;
    
    // ****************** graphic initializations ***********************
    //background
    sf::Texture bround;
    if (win_x == 1920) {
        if (!bround.loadFromFile("../Resources/Textures/BackgroundMenu_FHD.png")) {
            std::cerr << "Could not load BackgroundMenu_FHD.png" << std::endl;
        }
    }
    else if (win_x == 1280) {
        if (!bround.loadFromFile("../Resources/Textures/BackgroundMenu.png")) {
            std::cerr << "Could not load BackgroundMenu.png" << std::endl;
        }
    }
    sf::Sprite background(bround);

    //backEntities
    BackEntityManager backEntityManager;

    sf::Texture backEntity1_t;
    if (!backEntity1_t.loadFromFile("../Resources/Textures/ship_sprite7.png", sf::IntRect(13, 7, 537, 305))) {
        std::cerr << "Could not load ship_sprite7.png" << std::endl;
    }
    Equation eq1(1, 0, -300, 1, 0.23f, 1279, true);
    backEntityManager.spawn(eq1, backEntity1_t, 0.1f, 30.0f);
    
    //texts
    sf::Font font;
    if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }

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
                    sfx.play();
                    return GO_GAMEPLAY;
                }
                else if (buttonBounds(mousePos, options_txt)) {
                    sfx.play();
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, quit_txt)) {
                    sfx.play();
                    return QUIT;
                }
            }
        }
        backEntityManager.updateBackEntities(time);
        time = clock.restart().asSeconds();

        window.clear();
        window.draw(background);
        int backEntityManager_size = backEntityManager.getBackEntities_size();
        std::vector<BackEntity> backEntities = backEntityManager.getBackEntities();
        for (int i = 0; i < backEntityManager_size; i++) {
            window.draw(backEntities[i].getSprite());
        }
        window.draw(start_txt);
        window.draw(options_txt);
        window.draw(highscores_txt);
        window.draw(title_txt);
        window.draw(quit_txt);
        window.display();
    }

    std::cerr << "Error: displayMainMenu end of function return" << std::endl;
    return QUIT;
}


int Menu::displayOptions(sf::RenderWindow& window, sf::Music& music, sf::Sound& sfx) {

    // ****************** graphic initializations ***********************
    // background
    float win_x = (float)window.getSize().x;
    float win_y = (float)window.getSize().y;

    sf::Texture bround;
    if (win_x == 1920) {
        bround.loadFromFile("../Resources/Textures/BackgroundMenu_FHD.png");
    }
    else if (win_x == 1280) {
        bround.loadFromFile("../Resources/Textures/BackgroundMenu.png");
    }
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf"); 

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
    mvol_num_txt.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2) + mvol_bar.getLocalBounds().width + 25,
                              (win_y - mvol_num_txt.getLocalBounds().height) / 1.91f);

    sf::RectangleShape mvol_knob(sf::Vector2f(10, 25));
    mvol_knob.setOrigin(5, 13);
    mvol_knob.setFillColor(sf::Color::Magenta);

    mvol_knob.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2) + (mvol_bar.getLocalBounds().width * (mvol_num / 100)),
                           (win_y - mvol_bar.getLocalBounds().height) / 1.89f);

    sf::Text svol_txt("SFX Volume", font);
    svol_txt.setCharacterSize(25);
    svol_txt.setFillColor(sf::Color::White);
    svol_txt.setPosition(((win_x - svol_txt.getLocalBounds().width) / 1.51f),
                          (win_y - svol_txt.getLocalBounds().height) / 1.72f);

    sf::RectangleShape svol_bar(sf::Vector2f(230, 6));
    svol_bar.setFillColor(sf::Color::White);
    svol_bar.setPosition(((win_x - svol_bar.getLocalBounds().width) / 1.5f),
                          (win_y - svol_bar.getLocalBounds().height) / 1.59f);

    float svol_num = stof(readFromFile("sfx_volume"));
    sf::Text svol_num_txt(std::to_string(svol_num), font);
    svol_num_txt.setString(getVolPercentString(svol_num));
    svol_num_txt.setCharacterSize(20);
    svol_num_txt.setFillColor(sf::Color::White);
    svol_num_txt.setPosition(((win_x - svol_bar.getLocalBounds().width) / 1.5f) + svol_bar.getLocalBounds().width + 25,
                              (win_y - svol_num_txt.getLocalBounds().height) / 1.598f);

    sf::RectangleShape svol_knob(sf::Vector2f(10, 25));
    svol_knob.setOrigin(5, 13);
    svol_knob.setFillColor(sf::Color::Magenta);

    svol_knob.setPosition(((win_x - svol_bar.getLocalBounds().width) / 1.5f) + (svol_bar.getLocalBounds().width * (svol_num / 100)),
                           (win_y - svol_bar.getLocalBounds().height) / 1.585f);

    sf::Text muvol_txt("Music Volume", font);
    muvol_txt.setCharacterSize(25);
    muvol_txt.setFillColor(sf::Color::White);
    muvol_txt.setPosition(((win_x - muvol_txt.getLocalBounds().width) / 2.97f),
                           (win_y - muvol_txt.getLocalBounds().height) / 1.72f);

    sf::RectangleShape muvol_bar(sf::Vector2f(230, 6));
    muvol_bar.setFillColor(sf::Color::White);
    muvol_bar.setPosition(((win_x - muvol_bar.getLocalBounds().width) / 3),
                           (win_y - muvol_bar.getLocalBounds().height) / 1.59f);

    float muvol_num = stof(readFromFile("music_volume"));
    sf::Text muvol_num_txt(std::to_string(muvol_num), font);
    muvol_num_txt.setString(getVolPercentString(muvol_num));
    muvol_num_txt.setCharacterSize(20);
    muvol_num_txt.setFillColor(sf::Color::White);
    muvol_num_txt.setPosition(((win_x - muvol_bar.getLocalBounds().width) / 3) + muvol_bar.getLocalBounds().width + 25,
                               (win_y - muvol_num_txt.getLocalBounds().height) / 1.598f);

    sf::RectangleShape muvol_knob(sf::Vector2f(10, 25));
    muvol_knob.setOrigin(5, 13);
    muvol_knob.setFillColor(sf::Color::Magenta);

    muvol_knob.setPosition(((win_x - muvol_bar.getLocalBounds().width) / 3) + (muvol_bar.getLocalBounds().width * (muvol_num / 100)),
                            (win_y - muvol_bar.getLocalBounds().height) / 1.585f);

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
            else if (buttonBounds(mousePos, svol_knob)) {
                svol_knob.setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, muvol_knob)) {
                muvol_knob.setFillColor(sf::Color::Red);
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
                svol_knob.setFillColor(sf::Color::Magenta);
                muvol_knob.setFillColor(sf::Color::Magenta);
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
                    writeToFile(std::to_string(mvol_num), "main_volume");

                    music.setVolume(calcVolTotal().x);
                    sfx.setVolume(calcVolTotal().y);             
                    mvol_num_txt.setString(getVolPercentString(mvol_num));
                } 

                else if (buttonBounds(mousePos, svol_bar)) {

                    svol_knob.setPosition((float)mousePos.x, (win_y - svol_bar.getLocalBounds().height) / 1.585f);
                    svol_num = calcVolPercent((float)mousePos.x, svol_bar.getPosition().x);
                    writeToFile(std::to_string(svol_num), "sfx_volume");

                    sfx.setVolume(calcVolTotal().y);
                    svol_num_txt.setString(getVolPercentString(svol_num));
                }

                else if (buttonBounds(mousePos, muvol_bar)) {
                    muvol_knob.setPosition((float)mousePos.x, (win_y - muvol_bar.getLocalBounds().height) / 1.585f);
                    muvol_num = calcVolPercent((float)mousePos.x, muvol_bar.getPosition().x);
                    writeToFile(std::to_string(muvol_num), "music_volume");

                    music.setVolume(calcVolTotal().x);
                    muvol_num_txt.setString(getVolPercentString(muvol_num));
                }
            }

            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {   
                if (buttonBounds(mousePos, bind_txt)) {
                    sfx.play();
                    //key binds
                }
                else if (buttonBounds(mousePos, low_txt)) {
                    sfx.play();
                    window.create(sf::VideoMode(1280, 720), "Nebulon", sf::Style::Close);
                    writeToFile("1280x720", "resolution");
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, high_txt)) {
                    sfx.play();
                    window.create(sf::VideoMode(1920, 1080), "Nebulon", sf::Style::Close);
                    window.setPosition(sf::Vector2i(-8, -31));
                    writeToFile("1920x1080", "resolution");
                    return GO_OPTIONS_MENU;
                }
                else if (buttonBounds(mousePos, back_txt)) {
                    sfx.play();
                    return GO_MAIN_MENU;
                }
            }

            window.clear();
            window.draw(background);
            window.draw(options_txt);

            window.draw(mvol_txt);
            window.draw(mvol_bar);
            window.draw(mvol_num_txt);
            window.draw(mvol_knob);

            window.draw(svol_txt);
            window.draw(svol_bar);
            window.draw(svol_num_txt);
            window.draw(svol_knob);

            window.draw(muvol_txt);
            window.draw(muvol_bar);
            window.draw(muvol_num_txt);
            window.draw(muvol_knob);

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