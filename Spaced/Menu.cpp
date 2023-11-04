#include "Menu.h"

Menu::Menu() {
    //text font
    if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
        std::cerr << "Could not load font <MENU>" << std::endl;
    }

    //audio
    if (!music.openFromFile("../Resources/Audio/theme_music.ogg")) {
        std::cerr << "Could not load music <MENU>" << std::endl;
    }
    if (!sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
        std::cerr << "Could not load sfx <MENU>" << std::endl;
    }
    sfx.setBuffer(sfx_buffer);
    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    sfx.setVolume(sounds.y);
    music.play();

    //ship textures
    if (!movingEntities_t[0].loadFromFile("../Resources/Textures/ship_sprite7.png", sf::IntRect(14, 14, 525, 294)) ||
        !movingEntities_t[1].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(516, 770, 473, 164)) ||
        !movingEntities_t[2].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(516, 578, 473, 173)) ||
        !movingEntities_t[3].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(9, 163, 483, 163)) ||
        !movingEntities_t[4].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(14, 675, 479, 137)) ||
        !movingEntities_t[5].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(57, 537, 404, 112)) ||
        !movingEntities_t[6].loadFromFile("../Resources/Textures/ship_sprite9.png", sf::IntRect(27, 1, 975, 396))) {
        std::cerr << "Could not load ship textures <MENU>" << std::endl;
    }

    //background textures
    if (!backgroundFHD_t.loadFromFile("../Resources/Textures/BackgroundMenu_FHD.png") ||
        !background_t.loadFromFile("../Resources/Textures/BackgroundMenu.png") ||
        !transparent_t.loadFromFile("../Resources/Textures/TransparentMenu.png") ||
        !transparentFHD_t.loadFromFile("../Resources/Textures/TransparentMenu_FHD.png")) {
        std::cerr << "Could not load background textures <MENU>" << std::endl;
    }

    //resolution
    if (readFromFile("resolution").compare("1280x720") == 0) {
        fhd = false;
        background.setTexture(background_t);
        transparent.setTexture(transparent_t);
    }
    else {
        fhd = true;
        background.setTexture(backgroundFHD_t);
        transparent.setTexture(transparentFHD_t);
    }

    //moving ship sprites
    movingEntityManager = MovingEntityManager(movingEntities_t, fhd);
}


int Menu::displayMain(sf::RenderWindow& window) {
    loadUIMain(fhd);
    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

            // highlight button if mouse is over button
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonBounds(mousePos, UI_main["start_txt"])) {
                UI_main["start_txt"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_main["options_txt"])) {
                UI_main["options_txt"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_main["highscores_txt"])) {
                UI_main["highscores_txt"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_main["quit_txt"])) {
                UI_main["quit_txt"].setFillColor(sf::Color::Red);
            }
            else {
                UI_main["start_txt"].setFillColor(sf::Color::White);
                UI_main["options_txt"].setFillColor(sf::Color::White);
                UI_main["highscores_txt"].setFillColor(sf::Color::White);
                UI_main["quit_txt"].setFillColor(sf::Color::White);
            }

            // button actions
            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {
                if (buttonBounds(mousePos, UI_main["start_txt"])) {
                    sfx.play();
                    music.stop();
                    return GO_GAMEPLAY;
                }
                else if (buttonBounds(mousePos, UI_main["options_txt"])) {
                    sfx.play();
                    displayOptions(window);
                }
                else if (buttonBounds(mousePos, UI_main["quit_txt"])) {
                    sfx.play();
                    return QUIT;
                }
            }
        }
        movingEntityManager.update(time);
        movingEntityManager.spawn(movingEntities_t);
        time = clock.restart().asSeconds();

        window.clear();
        window.draw(background);

        //drawing ships behind buildings
        std::vector<MovingEntity> movingEntities1 = movingEntityManager.getMovingEntities1();
        int movingEntities1_size = movingEntityManager.getMovingEntities1_size();
        for (int i = 0; i < movingEntities1_size; i++) {
            window.draw(movingEntities1[i].getSprite());
        }
        window.draw(transparent);
        //drawing ships in front of buildings
        std::vector<MovingEntity> movingEntities2 = movingEntityManager.getMovingEntities2();
        int movingEntities2_size = movingEntityManager.getMovingEntities2_size();
        for (int i = 0; i < movingEntities2_size; i++) {
            window.draw(movingEntities2[i].getSprite());
        }
        window.draw(UI_main["start_txt"]);
        window.draw(UI_main["options_txt"]);
        window.draw(UI_main["highscores_txt"]);
        window.draw(UI_main["title_txt"]);
        window.draw(UI_main["quit_txt"]);
        window.draw(UI_main["lives_txt"]);
        window.display();
    }

    std::cerr << "Error: displayMainMenu end of function return" << std::endl;
    return QUIT;
}



int Menu::displayOptions(sf::RenderWindow& window) {
    //resolution
    int win_x = 1280;
    int win_y = 720;
    if (fhd) {
        win_x = 1920;
        win_y = 1080;
    }
    loadUIOptions(fhd);
    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window.close();
                break;
            }

            //highlight button if mouse is over button  
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (buttonBounds(mousePos, UI_options2["mvol_knob"])) {
                UI_options2["mvol_knob"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_options2["svol_knob"])) {
                UI_options2["svol_knob"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_options2["muvol_knob"])) {
                UI_options2["muvol_knob"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_options["bind_txt"])) {
                UI_options["bind_txt"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_options["back_txt"])) {
                UI_options["back_txt"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_options["low_txt"])) {
                UI_options["low_txt"].setFillColor(sf::Color::Red);
            }
            else if (buttonBounds(mousePos, UI_options["high_txt"])) {
                UI_options["high_txt"].setFillColor(sf::Color::Red);
            }
            else {
                UI_options2["mvol_knob"].setFillColor(sf::Color::Magenta);
                UI_options2["svol_knob"].setFillColor(sf::Color::Magenta);
                UI_options2["muvol_knob"].setFillColor(sf::Color::Magenta);
                UI_options["bind_txt"].setFillColor(sf::Color::White);
                UI_options["back_txt"].setFillColor(sf::Color::White);
                UI_options["low_txt"].setFillColor(sf::Color::White);
                UI_options["high_txt"].setFillColor(sf::Color::White);
            }

            //mouse tracker alternative for volume slider
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (buttonBounds(mousePos, UI_options2["mvol_bar"])) {
                    UI_options2["mvol_knob"].setPosition((float)mousePos.x, (win_y - UI_options2["mvol_bar"].getLocalBounds().height) / 1.89f);
                    float mvol_num = calcVolPercent((float)mousePos.x, UI_options2["mvol_bar"].getPosition().x);
                    writeToFile(std::to_string(mvol_num), "main_volume");

                    sf::Vector2f sounds = calcVolTotal();
                    music.setVolume(sounds.x);
                    sfx.setVolume(sounds.y);             
                    UI_options["mvol_num_txt"].setString(getVolPercentString(mvol_num));
                } 
                else if (buttonBounds(mousePos, UI_options2["svol_bar"])) {
                    UI_options2["svol_knob"].setPosition((float)mousePos.x, (win_y - UI_options2["svol_bar"].getLocalBounds().height) / 1.585f);
                    float svol_num = calcVolPercent((float)mousePos.x, UI_options2["svol_bar"].getPosition().x);
                    writeToFile(std::to_string(svol_num), "sfx_volume");

                    sfx.setVolume(calcVolTotal().y);
                    UI_options["svol_num_txt"].setString(getVolPercentString(svol_num));
                }
                else if (buttonBounds(mousePos, UI_options2["muvol_bar"])) {
                    UI_options2["muvol_knob"].setPosition((float)mousePos.x, (win_y - UI_options2["muvol_bar"].getLocalBounds().height) / 1.585f);
                    float muvol_num = calcVolPercent((float)mousePos.x, UI_options2["muvol_bar"].getPosition().x);
                    writeToFile(std::to_string(muvol_num), "music_volume");

                    music.setVolume(calcVolTotal().x);
                    UI_options["muvol_num_txt"].setString(getVolPercentString(muvol_num));
                }
            }

            // button actions
            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {   
                if (buttonBounds(mousePos, UI_options["bind_txt"])) {
                    sfx.play();
                    //key binds
                }
                else if (buttonBounds(mousePos, UI_options["low_txt"])) {
                    sfx.play();
                    window.create(sf::VideoMode(1280, 720), "Nebulon", sf::Style::Close);
                    resolutionReset(movingEntities_t, false);
                    loadUIMain(fhd);
                    loadUIOptions(fhd);
                    win_x = 1280;
                    win_y = 720;
                }
                else if (buttonBounds(mousePos, UI_options["high_txt"])) {
                    sfx.play();
                    window.create(sf::VideoMode(1920, 1080), "Nebulon", sf::Style::Close);
                    window.setPosition(sf::Vector2i(-8, -31));
                    resolutionReset(movingEntities_t, true);
                    loadUIMain(fhd);
                    loadUIOptions(fhd);
                    win_x = 1920;
                    win_y = 1080;
                }
                else if (buttonBounds(mousePos, UI_options["back_txt"])) {
                    sfx.play();
                    return GO_MAIN_MENU;
                }
            }
        }
        movingEntityManager.update(time);
        movingEntityManager.spawn(movingEntities_t);
        time = clock.restart().asSeconds();

        window.clear();
        window.draw(background);
        //drawing ship sprites behind and in front of buildings
        int movingEntities1_size = movingEntityManager.getMovingEntities1_size();
        std::vector<MovingEntity> movingEntities1 = movingEntityManager.getMovingEntities1();
        //front
        for (int i = 0; i < movingEntities1_size; i++) {
            window.draw(movingEntities1[i].getSprite());
        }
        window.draw(transparent); 
        //behind
        int movingEntities2_size = movingEntityManager.getMovingEntities2_size();
        std::vector<MovingEntity> movingEntities2 = movingEntityManager.getMovingEntities2();
        for (int i = 0; i < movingEntities2_size; i++) {
            window.draw(movingEntities2[i].getSprite());
        }
        window.draw(UI_options["options_txt"]);
        window.draw(UI_options["mvol_txt"]);
        window.draw(UI_options2["mvol_bar"]);
        window.draw(UI_options["mvol_num_txt"]);
        window.draw(UI_options2["mvol_knob"]);
        window.draw(UI_options["svol_txt"]);
        window.draw(UI_options2["svol_bar"]);
        window.draw(UI_options["svol_num_txt"]);
        window.draw(UI_options2["svol_knob"]);
        window.draw(UI_options["muvol_txt"]);
        window.draw(UI_options2["muvol_bar"]);
        window.draw(UI_options["muvol_num_txt"]);
        window.draw(UI_options2["muvol_knob"]);
        window.draw(UI_options["bind_txt"]);
        window.draw(UI_options["low_txt"]);
        window.draw(UI_options["high_txt"]);
        window.draw(UI_options["back_txt"]);
        window.display();
    }

    std::cerr << "Error: displayOptionsMenu end of function return" << std::endl;
    return QUIT;
}



void Menu::resolutionReset(sf::Texture* movingEntities_t, bool fhd) {
    movingEntityManager = MovingEntityManager(movingEntities_t, fhd);
    if (fhd) {
        writeToFile("1920x1080", "resolution");
        background = sf::Sprite();
        background.setTexture(backgroundFHD_t);
        transparent = sf::Sprite();
        transparent.setTexture(transparentFHD_t);
        this->fhd = fhd;
    }
    else {
        writeToFile("1280x720", "resolution");
        background = sf::Sprite();
        background.setTexture(background_t);
        transparent = sf::Sprite();
        transparent.setTexture(transparent_t);
        this->fhd = fhd;
    }
}



void Menu::loadUIMain(bool fhd) {
    //resolution
    int win_x = 1280;
    int win_y = 720;
    if (fhd) {
        win_x = 1920;
        win_y = 1080;
    }

    //texts
    int lives = stoi(readFromFile("lives"));
    sf::Text lives_txt(std::to_string(lives), font);
    if (lives == 1) {
        lives_txt.setString(std::to_string(lives) + " drone left");
    }
    else {
        lives_txt.setString(std::to_string(lives) + " drones left");
    }
    lives_txt.setCharacterSize(20);
    lives_txt.setFillColor(sf::Color::White);
    lives_txt.setPosition(((win_x - lives_txt.getLocalBounds().width) / 1.23f) + lives_txt.getLocalBounds().width + 25,
        (win_y - lives_txt.getLocalBounds().height) / 45);
    UI_main["lives_txt"] = lives_txt;

    sf::Text title_txt("Nebulon", font);
    title_txt.setCharacterSize(60);
    title_txt.setStyle(sf::Text::Bold);
    title_txt.setFillColor(sf::Color::White);
    title_txt.setPosition(((win_x - title_txt.getLocalBounds().width) / 2.0f),
        (win_y - title_txt.getLocalBounds().height) / 3.5f);
    UI_main["title_txt"] = title_txt;

    sf::Text start_txt("Start", font);
    start_txt.setCharacterSize(30);
    start_txt.setStyle(sf::Text::Bold);
    start_txt.setFillColor(sf::Color::White);
    start_txt.setPosition(((win_x - start_txt.getLocalBounds().width) / 2.0f),
        (win_y - start_txt.getLocalBounds().height) / 1.8f);
    UI_main["start_txt"] = start_txt;

    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(30);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition(((win_x - options_txt.getLocalBounds().width) / 2.0f),
        (win_y - options_txt.getLocalBounds().height) / 1.6f);
    UI_main["options_txt"] = options_txt;

    sf::Text highscores_txt("Highscores", font);
    highscores_txt.setCharacterSize(30);
    highscores_txt.setStyle(sf::Text::Bold);
    highscores_txt.setFillColor(sf::Color::White);
    highscores_txt.setPosition(((win_x - highscores_txt.getLocalBounds().width) / 2.0f),
        (win_y - highscores_txt.getLocalBounds().height) / 1.44f);
    UI_main["highscores_txt"] = highscores_txt;

    sf::Text quit_txt("Quit", font);
    quit_txt.setCharacterSize(30);
    quit_txt.setStyle(sf::Text::Bold);
    quit_txt.setFillColor(sf::Color::White);
    quit_txt.setPosition(((win_x - quit_txt.getLocalBounds().width) / 2.0f),
        (win_y - quit_txt.getLocalBounds().height) / 1.32f);
    UI_main["quit_txt"] = quit_txt;
}



void Menu::loadUIOptions(bool fhd) {
    //resolution
    int win_x = 1280;
    int win_y = 720;
    if (fhd) {
        win_x = 1920;
        win_y = 1080;
    }

    //texts
    sf::Text options_txt("Options", font);
    options_txt.setCharacterSize(45);
    options_txt.setStyle(sf::Text::Bold);
    options_txt.setFillColor(sf::Color::White);
    options_txt.setPosition(((win_x - options_txt.getLocalBounds().width) / 2),
        (win_y - options_txt.getLocalBounds().height) / 3.5f);
    UI_options["options_txt"] = options_txt;

    sf::Text mvol_txt("Main Volume", font);
    mvol_txt.setCharacterSize(25);
    mvol_txt.setFillColor(sf::Color::White);
    mvol_txt.setPosition(((win_x - mvol_txt.getLocalBounds().width) / 2),
        (win_y - mvol_txt.getLocalBounds().height) / 2.1f);
    UI_options["mvol_txt"] = mvol_txt;

    sf::RectangleShape mvol_bar(sf::Vector2f(230, 6));
    mvol_bar.setFillColor(sf::Color::White);
    mvol_bar.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2),
        (win_y - mvol_bar.getLocalBounds().height) / 1.9f);
    UI_options2["mvol_bar"] = mvol_bar;

    float mvol_num = stof(readFromFile("main_volume"));
    sf::Text mvol_num_txt(std::to_string(mvol_num), font);
    mvol_num_txt.setString(getVolPercentString(mvol_num));
    mvol_num_txt.setCharacterSize(20);
    mvol_num_txt.setFillColor(sf::Color::White);
    mvol_num_txt.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2) + mvol_bar.getLocalBounds().width + 25,
        (win_y - mvol_num_txt.getLocalBounds().height) / 1.91f);
    UI_options["mvol_num_txt"] = mvol_num_txt;

    sf::RectangleShape mvol_knob(sf::Vector2f(10, 25));
    mvol_knob.setOrigin(5, 13);
    mvol_knob.setFillColor(sf::Color::Magenta);
    mvol_knob.setPosition(((win_x - mvol_bar.getLocalBounds().width) / 2) + (mvol_bar.getLocalBounds().width * (mvol_num / 100)),
        (win_y - mvol_bar.getLocalBounds().height) / 1.89f);
    UI_options2["mvol_knob"] = mvol_knob;

    sf::Text svol_txt("SFX Volume", font);
    svol_txt.setCharacterSize(25);
    svol_txt.setFillColor(sf::Color::White);
    svol_txt.setPosition(((win_x - svol_txt.getLocalBounds().width) / 1.51f),
        (win_y - svol_txt.getLocalBounds().height) / 1.72f);
    UI_options["svol_txt"] = svol_txt;

    sf::RectangleShape svol_bar(sf::Vector2f(230, 6));
    svol_bar.setFillColor(sf::Color::White);
    svol_bar.setPosition(((win_x - svol_bar.getLocalBounds().width) / 1.5f),
        (win_y - svol_bar.getLocalBounds().height) / 1.59f);
    UI_options2["svol_bar"] = svol_bar;

    float svol_num = stof(readFromFile("sfx_volume"));
    sf::Text svol_num_txt(std::to_string(svol_num), font);
    svol_num_txt.setString(getVolPercentString(svol_num));
    svol_num_txt.setCharacterSize(20);
    svol_num_txt.setFillColor(sf::Color::White);
    svol_num_txt.setPosition(((win_x - svol_bar.getLocalBounds().width) / 1.5f) + svol_bar.getLocalBounds().width + 25,
        (win_y - svol_num_txt.getLocalBounds().height) / 1.598f);
    UI_options["svol_num_txt"] = svol_num_txt;

    sf::RectangleShape svol_knob(sf::Vector2f(10, 25));
    svol_knob.setOrigin(5, 13);
    svol_knob.setFillColor(sf::Color::Magenta);
    svol_knob.setPosition(((win_x - svol_bar.getLocalBounds().width) / 1.5f) + (svol_bar.getLocalBounds().width * (svol_num / 100)),
        (win_y - svol_bar.getLocalBounds().height) / 1.585f);
    UI_options2["svol_knob"] = svol_knob;

    sf::Text muvol_txt("Music Volume", font);
    muvol_txt.setCharacterSize(25);
    muvol_txt.setFillColor(sf::Color::White);
    muvol_txt.setPosition(((win_x - muvol_txt.getLocalBounds().width) / 2.97f),
        (win_y - muvol_txt.getLocalBounds().height) / 1.72f);
    UI_options["muvol_txt"] = muvol_txt;

    sf::RectangleShape muvol_bar(sf::Vector2f(230, 6));
    muvol_bar.setFillColor(sf::Color::White);
    muvol_bar.setPosition(((win_x - muvol_bar.getLocalBounds().width) / 3),
        (win_y - muvol_bar.getLocalBounds().height) / 1.59f);
    UI_options2["muvol_bar"] = muvol_bar;

    float muvol_num = stof(readFromFile("music_volume"));
    sf::Text muvol_num_txt(std::to_string(muvol_num), font);
    muvol_num_txt.setString(getVolPercentString(muvol_num));
    muvol_num_txt.setCharacterSize(20);
    muvol_num_txt.setFillColor(sf::Color::White);
    muvol_num_txt.setPosition(((win_x - muvol_bar.getLocalBounds().width) / 3) + muvol_bar.getLocalBounds().width + 25,
        (win_y - muvol_num_txt.getLocalBounds().height) / 1.598f);
    UI_options["muvol_num_txt"] = muvol_num_txt;

    sf::RectangleShape muvol_knob(sf::Vector2f(10, 25));
    muvol_knob.setOrigin(5, 13);
    muvol_knob.setFillColor(sf::Color::Magenta);
    muvol_knob.setPosition(((win_x - muvol_bar.getLocalBounds().width) / 3) + (muvol_bar.getLocalBounds().width * (muvol_num / 100)),
        (win_y - muvol_bar.getLocalBounds().height) / 1.585f);
    UI_options2["muvol_knob"] = muvol_knob;

    sf::Text bind_txt("Key Bindings", font);
    bind_txt.setCharacterSize(30);
    bind_txt.setFillColor(sf::Color::White);
    bind_txt.setPosition(((win_x - bind_txt.getLocalBounds().width) / 2),
        (win_y - bind_txt.getLocalBounds().height) / 1.44f);
    UI_options["bind_txt"] = bind_txt;

    sf::Text low_txt("1280x720", font);
    low_txt.setCharacterSize(28);
    low_txt.setFillColor(sf::Color::White);
    low_txt.setPosition(((win_x - low_txt.getLocalBounds().width) / 2.4f),
        (win_y - low_txt.getLocalBounds().height) / 1.32f);
    UI_options["low_txt"] = low_txt;

    sf::Text high_txt("1920x1080", font);
    high_txt.setCharacterSize(28);
    high_txt.setFillColor(sf::Color::White);
    high_txt.setPosition(((win_x - low_txt.getLocalBounds().width) / 1.72f),
        (win_y - high_txt.getLocalBounds().height) / 1.32f);
    UI_options["high_txt"] = high_txt;

    sf::Text back_txt("Back", font);
    back_txt.setCharacterSize(30);
    back_txt.setFillColor(sf::Color::White);
    back_txt.setPosition(((win_x - back_txt.getLocalBounds().width) / 2),
        (win_y - back_txt.getLocalBounds().height) / 1.22f);
    UI_options["back_txt"] = back_txt;
}