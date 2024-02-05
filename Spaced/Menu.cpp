#include "Menu.h"


Menu::Menu(sf::RenderWindow* window) {
    this->window = window;

    //text font
    if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
        std::cerr << "Font load error <MENU>" << std::endl;
    }

    //audio
    if (!music.openFromFile("../Resources/Audio/theme_music.ogg") ||
        sfx_buffer.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
        std::cerr << "Audio load error <MENU>" << std::endl;
    }
    sfx.setBuffer(sfx_buffer);
    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    sfx.setVolume(sounds.y);
    music.play();

    //ship textures
    if (!textures["background"].loadFromFile("../Resources/Textures/BackgroundMenu.png") ||
        !textures["transparent"].loadFromFile("../Resources/Textures/TransparentMenu.png") ||
        !textures["transparentFHD"].loadFromFile("../Resources/Textures/TransparentMenu_FHD.png") ||
        !textures["entity0"].loadFromFile("../Resources/Textures/ship_sprite7.png", sf::IntRect(14, 14, 525, 294)) ||
        !textures["entity1"].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(516, 770, 473, 164)) ||
        !textures["entity2"].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(516, 578, 473, 173)) ||
        !textures["entity3"].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(9, 163, 483, 163)) ||
        !textures["entity4"].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(14, 675, 479, 137)) ||
        !textures["entity5"].loadFromFile("../Resources/Textures/ship_sprite8.png", sf::IntRect(57, 537, 404, 112)) ||
        !textures["entity6"].loadFromFile("../Resources/Textures/ship_sprite9.png", sf::IntRect(27, 1, 975, 396))) {
        std::cerr << "Textures load error <MENU>" << std::endl;
    }

    UIsprites["background"].setTexture(textures["background"]);
    UIsprites["transparent"].setTexture(textures["transparent"]);

    //entity manager flags for timed spawn
    int entities_flags_size = sizeof(entities_flags);
    for (int i = 0; i < entities_flags_size; i++) {
        entities_flags[i] = false;
    }

    win_x = 1280;
    win_y = 720;

    loadUIMain();
    loadUIOptions();
}

int Menu::displayMain() {
    loadUIMain();
    while (window->isOpen()) {
        sf::Event evnt;
        while (window->pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window->close();
            }

            //highlight button if mouse is hovered over it
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            highlightButtonMain(mousePos);

            // button actions
            if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left) {
                int go = buttonPressedMain(mousePos);
                if (go == GO_OPTIONS_MENU) {
                    displayOptions();
                }
                else if (go == NULL) {
                    continue;
                }
                else {
                    return go;
                }
            }
        }
        spawnEntities();
        updateEntityPosition();

        window->clear();
        window->draw(UIsprites["background"]);
        //drawing ships in front and behind buildings
        //behind
        size_t entities_back_size = entities_back.size();
        for (int i = 0; i < entities_back_size; i++) {
            window->draw(entities_back[i].getSprite());
        }
        window->draw(UIsprites["transparent"]);
        //front
        size_t entities_front_size = entities_front.size();
        for (int i = 0; i < entities_front_size; i++) {
            window->draw(entities_front[i].getSprite());
        }
        window->draw(UI_main["start_txt"]);
        window->draw(UI_main["options_txt"]);
        window->draw(UI_main["highscores_txt"]);
        window->draw(UI_main["title_txt"]);
        window->draw(UI_main["quit_txt"]);
        window->draw(UI_main["lives_txt"]);
        window->display();
    }

    std::cerr << "Error: displayMainMenu end of function return" << std::endl;
    return QUIT;
}

int Menu::displayOptions() {
    loadUIOptions();
    while (window->isOpen()) {
        sf::Event evnt;
        while (window->pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window->close();
                break;
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            highlightButtonOptions(mousePos);
            volumeSliderOptions(mousePos);

            // button actions
            if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left) {
                if (buttonPressedOptions(mousePos) == GO_MAIN_MENU) {
                    return NULL;
                }
            }
        }       
        spawnEntities();
        updateEntityPosition();

        window->clear();
        window->draw(UIsprites["background"]);
        //drawing ships in front and behind buildings
        size_t entities_back_size = entities_back.size();
        for (int i = 0; i < entities_back_size; i++) {
            window->draw(entities_back[i].getSprite());
        }
        window->draw(UIsprites["transparent"]);
        //front
        size_t entities_front_size = entities_front.size();
        for (int i = 0; i < entities_front_size; i++) {
            window->draw(entities_front[i].getSprite());
        }
        window->draw(UI_options["options_txt"]);
        window->draw(UI_options["mvol_txt"]);
        window->draw(UI_options2["mvol_bar"]);
        window->draw(UI_options["mvol_num_txt"]);
        window->draw(UI_options2["mvol_knob"]);
        window->draw(UI_options["svol_txt"]);
        window->draw(UI_options2["svol_bar"]);
        window->draw(UI_options["svol_num_txt"]);
        window->draw(UI_options2["svol_knob"]);
        window->draw(UI_options["muvol_txt"]);
        window->draw(UI_options2["muvol_bar"]);
        window->draw(UI_options["muvol_num_txt"]);
        window->draw(UI_options2["muvol_knob"]);
        window->draw(UI_options["bind_txt"]);
        window->draw(UI_options["low_txt"]);
        window->draw(UI_options["high_txt"]);
        window->draw(UI_options["back_txt"]);
        window->display();
    }

    std::cerr << "Error: displayOptionsMenu end of function return" << std::endl;
    return QUIT;
}

void Menu::highlightButtonMain(sf::Vector2i mousePos) {
    if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["start_txt"])) {
        UI_main["start_txt"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["options_txt"])) {
        UI_main["options_txt"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["highscores_txt"])) {
        UI_main["highscores_txt"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["quit_txt"])) {
        UI_main["quit_txt"].setFillColor(sf::Color::Red);
    }
    else {
        UI_main["start_txt"].setFillColor(sf::Color::White);
        UI_main["options_txt"].setFillColor(sf::Color::White);
        UI_main["highscores_txt"].setFillColor(sf::Color::White);
        UI_main["quit_txt"].setFillColor(sf::Color::White);
    }
}

void Menu::highlightButtonOptions(sf::Vector2i mousePos) {
    if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options2["mvol_knob"])) {
        UI_options2["mvol_knob"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options2["svol_knob"])) {
        UI_options2["svol_knob"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options2["muvol_knob"])) {
        UI_options2["muvol_knob"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["bind_txt"])) {
        UI_options["bind_txt"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["back_txt"])) {
        UI_options["back_txt"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["low_txt"])) {
        UI_options["low_txt"].setFillColor(sf::Color::Red);
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["high_txt"])) {
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
}

int Menu::buttonPressedMain(sf::Vector2i mousePos) {
    if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["start_txt"])) {
        sfx.play();
        music.stop();
        return GO_GAMEPLAY;
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["options_txt"])) {
        sfx.play();
        return GO_OPTIONS_MENU;
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_main["quit_txt"])) {
        sfx.play();
        return QUIT;
    }
    return NULL;
}

int Menu::buttonPressedOptions(sf::Vector2i mousePos) {
    if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["bind_txt"])) {
        sfx.play();
        //key binds
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["low_txt"])) {
        window->setSize(sf::Vector2u(1280, 720));
        sf::VideoMode screen_size = sf::VideoMode::getDesktopMode();
        window->setPosition(sf::Vector2i(screen_size.width / 2 - 640, screen_size.height / 2 - 360));
        sfx.play();
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["high_txt"])) {
        sfx.play();
        window->setSize(sf::Vector2u(1920, 1080));
        sf::VideoMode screen_size = sf::VideoMode::getDesktopMode();
        window->setPosition(sf::Vector2i(screen_size.width / 2 - 968, screen_size.height / 2 - 571));
    }
    else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options["back_txt"])) {
        sfx.play();
        return GO_MAIN_MENU;
    }
    return NULL;
}

void Menu::volumeSliderOptions(sf:: Vector2i mousePos) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options2["mvol_bar"])) {
            UI_options2["mvol_knob"].setPosition(window->mapPixelToCoords(mousePos).x, 377);
            float mvol_num = calcVolPercent(window->mapPixelToCoords(mousePos).x, UI_options2["mvol_bar"].getPosition().x);
            writeToFile(std::to_string(mvol_num), "main_volume");

            sf::Vector2f sounds = calcVolTotal();
            music.setVolume(sounds.x);
            sfx.setVolume(sounds.y);
            UI_options["mvol_num_txt"].setString(getVolPercentString(mvol_num));
        }
        else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options2["svol_bar"])) {
            UI_options2["svol_knob"].setPosition(window->mapPixelToCoords(mousePos).x, 450);
            float svol_num = calcVolPercent(window->mapPixelToCoords(mousePos).x, UI_options2["svol_bar"].getPosition().x);
            writeToFile(std::to_string(svol_num), "sfx_volume");

            sfx.setVolume(calcVolTotal().y);
            UI_options["svol_num_txt"].setString(getVolPercentString(svol_num));
        }
        else if (buttonBounds(window->mapPixelToCoords(mousePos), UI_options2["muvol_bar"])) {
            UI_options2["muvol_knob"].setPosition(window->mapPixelToCoords(mousePos).x, 450);
            float muvol_num = calcVolPercent(window->mapPixelToCoords(mousePos).x, UI_options2["muvol_bar"].getPosition().x);
            writeToFile(std::to_string(muvol_num), "music_volume");

            music.setVolume(calcVolTotal().x);
            UI_options["muvol_num_txt"].setString(getVolPercentString(muvol_num));
        }
    }
}

void Menu::loadUIMain() {
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
    UI_main["quit_txt"] = quit_txt;
}

void Menu::loadUIOptions() {
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

void Menu::spawnEntities() {
    float MAX = 3000;
    float MIN = -1000;
    int mem_time = (int)entities_clock.getElapsedTime().asSeconds();

    if (mem_time == 0 && entities_flags[0] == false) {
        Entity e0(textures["entity0"], 1280, 35); //top right, fast
        e0.push_back(Equation(1, 0, -300, 1, 0.23f, MIN, 1, true));
        e0.setScale(0.07f, 0.07f);

        Entity e1(textures["entity1"], -135, 8); //mid left, lower
        e1.push_back(Equation(0, 0, -300, 0, 0, MAX, 1, false));
        e1.setScale(0.3f, 0.3f);

        Entity e3(textures["entity3"], 1020, 5); //bottom right, behind tower
        e3.push_back(Equation(0, 0, -450, 0, 0, MIN, 1, true));
        e3.setScale(0.2f, 0.2f);

        Entity e5(textures["entity5"], 1280, 15); //top right, lower
        e5.push_back(Equation(0, 0, -175, 0, 0, MIN, 1, true));
        e5.setScale(0.5f, 0.5f);

        Entity e6(textures["entity6"], 200, 3); //bottom left, behind tower
        e6.push_back(Equation(0, 0, -400, 0, 0, MAX, 1, false));
        e6.setScale(0.1f, 0.1f);

        entities_front.push_back(e0);
        entities_back.push_back(e3);
        entities_back.push_back(e1);
        entities_front.push_back(e5);
        entities_back.push_back(e6);

        entities_flags[0] = true;
    }
    else if (mem_time == 10 && entities_flags[1] == false) {
        Entity e2(textures["entity2"], -102, 8); //mid left, upper
        e2.push_back(Equation(0, 0, -260, 0, 0, MAX, 1, false));
        e2.setScale(0.22f, 0.22f);

        Entity e4(textures["entity4"], 1278, 15); //top right, higher
        e4.push_back(Equation(0, 0, -100, 0, 0, MIN, 1, true));
        e4.setScale(0.5f, 0.5f);

        entities_back.push_back(e2);
        entities_front.push_back(e4);

        entities_flags[1] = true;
    }
    else if (mem_time == 70 && entities_flags[2] == false) {
        Entity e0(textures["entity0"], 1280, 35); //mid left, fast
        e0.push_back(Equation(1, 0, -400, 1, 0.1f, MIN, 1, true));
        e0.setScale(0.07f, 0.07f);
        e0.setRotation(10);


        entities_front.push_back(e0);

        entities_flags[2] = true;
    }
    else if (mem_time == 140) {
        int mem_flags_size = sizeof(entities_flags);
        for (int i = 0; i < mem_flags_size; i++) {
            entities_flags[i] = false;
        }
        entities_clock.restart();
    }
}

void Menu::updateEntityPosition() {
    sf::FloatRect boundary(0, 0, 1280, 720);
    float frame_time = frame_clock.getElapsedTime().asSeconds();
    frame_clock.restart();

    for (int i = 0; i < entities_front.size(); i++) {
        entities_front[i].update(frame_time);
        //bounds check
        sf::FloatRect pos = entities_front[i].getGlobalBounds();
        if (!boundary.intersects(pos)) {
            entities_front.erase(entities_front.begin() + i);
        }
    }

    for (int i = 0; i < entities_back.size(); i++) {
        entities_back[i].update(frame_time);
        //bounds check
        sf::FloatRect pos = entities_back[i].getGlobalBounds();
        if (!boundary.intersects(pos)) {
            entities_back.erase(entities_back.begin() + i);
        }
    }
}

/* BUGS */
//FIX ENEMY ATTACK POSITIONING



/* IMPLEMENTATIONS */
//ADD BOSS HEALTH UI