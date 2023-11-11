#include "Menu.h"

Menu::Menu(sf::RenderWindow* window) {
    this->window = window;

    int mem_flags_size = sizeof(em_flags);
    for (int i = 0; i < mem_flags_size; i++) {
        em_flags[i] = false;
    }
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
    if (!textures["backgroundFHD"].loadFromFile("../Resources/Textures/BackgroundMenu_FHD.png") ||
        !textures["background"].loadFromFile("../Resources/Textures/BackgroundMenu.png") ||
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

    //resolution
    if (readFromFile("resolution").compare("1280x720") == 0) {
        fhd = false;
        win_x = 1280;
        win_y = 720;
        background.setTexture(textures["background"]);
        transparent.setTexture(textures["transparent"]);
    }
    else {
        fhd = true;
        win_x = 1920;
        win_y = 1080;
        background.setTexture(textures["backgroundFHD"]);
        transparent.setTexture(textures["transparentFHD"]);
    }

    loadUIMain(fhd);
    loadUIOptions(fhd);
}


int Menu::displayMain() {
    loadUIMain(fhd);
    while (window->isOpen()) {
        sf::Event evnt;
        while (window->pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window->close();
            }

            //highlight button if mouse is hovered over it
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            highlightMain(mousePos);

            // button actions
            if (evnt.mouseButton.button == sf::Mouse::Left) {
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
        updateEntities();

        window->clear();
        window->draw(background);
        //drawing ships in front and behind buildings
        //behind
        std::vector<Entity> movingEntities_back = em_back.getEntities();
        int mem_back_size = em_back.getSize();
        for (int i = 0; i < mem_back_size; i++) {
            window->draw(movingEntities_back[i].getSprite());
        }
        window->draw(transparent);
        //front
        std::vector<Entity> movingEntities_front = em_front.getEntities();
        int movingEntities2_size = em_front.getSize();
        for (int i = 0; i < movingEntities2_size; i++) {
            window->draw(movingEntities_front[i].getSprite());
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
    loadUIOptions(fhd);
    while (window->isOpen()) {
        sf::Event evnt;
        while (window->pollEvent(evnt)) {
            if (evnt.type == sf::Event::Closed) {
                window->close();
                break;
            }

            //highlight button if mouse is hovered over it
            sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
            highlightOptions(mousePos);

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
            if (evnt.mouseButton.button == sf::Mouse::Left) {
                if (buttonPressedOptions(mousePos) == GO_MAIN_MENU) {
                    return NULL;
                }
            }
        }       
        updateEntities();

        window->clear();
        window->draw(background);
        //drawing ships in front and behind buildings
        int mem_back_size = em_back.getSize();
        std::vector<Entity> movingEntities_back = em_back.getEntities();
        //behind
        for (int i = 0; i < mem_back_size; i++) {
            window->draw(movingEntities_back[i].getSprite());
        }
        window->draw(transparent);
        //front
        int mem_front_size = em_front.getSize();
        std::vector<Entity> movingEntities_front = em_front.getEntities();
        for (int i = 0; i < mem_front_size; i++) {
            window->draw(movingEntities_front[i].getSprite());
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



void Menu::highlightMain(sf::Vector2i mousePos) {
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
}



void Menu::highlightOptions(sf::Vector2i mousePos) {
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
}



int Menu::buttonPressedMain(sf::Vector2i mousePos) {
    if (buttonBounds(mousePos, UI_main["start_txt"])) {
        sfx.play();
        music.stop();
        return GO_GAMEPLAY;
    }
    else if (buttonBounds(mousePos, UI_main["options_txt"])) {
        sfx.play();
        return GO_OPTIONS_MENU;
    }
    else if (buttonBounds(mousePos, UI_main["quit_txt"])) {
        sfx.play();
        return QUIT;
    }
    return NULL;
}



int Menu::buttonPressedOptions(sf::Vector2i mousePos) {
    if (buttonBounds(mousePos, UI_options["bind_txt"])) {
        sfx.play();
        //key binds
    }
    else if (buttonBounds(mousePos, UI_options["low_txt"])) {
        sfx.play();
        window->create(sf::VideoMode(1280, 720), "Nebulon", sf::Style::Close);
        resolutionReset(false);
        loadUIMain(fhd);
        loadUIOptions(fhd);
        win_x = 1280;
        win_y = 720;
    }
    else if (buttonBounds(mousePos, UI_options["high_txt"])) {
        sfx.play();
        window->create(sf::VideoMode(1920, 1080), "Nebulon", sf::Style::Close);
        window->setPosition(sf::Vector2i(-8, -31));
        resolutionReset(true);
        loadUIMain(fhd);
        loadUIOptions(fhd);
        win_x = 1920;
        win_y = 1080;
    }
    else if (buttonBounds(mousePos, UI_options["back_txt"])) {
        sfx.play();
        return GO_MAIN_MENU;
    }
    return NULL;
}



void Menu::resolutionReset(bool fhd) {
    em_back = EntityManager(fhd);
    em_front = EntityManager(fhd);
    em_clock.restart();   
    int mem_flags_size = sizeof(em_flags);
    for (int i = 0; i < mem_flags_size; i++) {
        em_flags[i] = false;
    }

    if (fhd) {
        writeToFile("1920x1080", "resolution");
        background = sf::Sprite();
        background.setTexture(textures["backgroundFHD"]);
        transparent = sf::Sprite();
        transparent.setTexture(textures["transparentFHD"]);
        this->fhd = fhd;
        win_x = 1920;
        win_y = 1080;
    }
    else {
        writeToFile("1280x720", "resolution");
        background = sf::Sprite();
        background.setTexture(textures["background"]);
        transparent = sf::Sprite();
        transparent.setTexture(textures["transparent"]);
        this->fhd = fhd;
        win_x = 1280;
        win_y = 720;
    }
}



void Menu::loadUIMain(bool fhd) {
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

    em_back = EntityManager(fhd);
    em_front = EntityManager(fhd);
}



void Menu::loadUIOptions(bool fhd) {
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



void Menu::updateEntities() {
    float MAX = 3000;
    float MIN = -1000;

    float mem_time = em_clock.getElapsedTime().asSeconds();

    if ((int)mem_time == 0 && em_flags[0] == false) {
        //          pt, xt, yt, m_xt, m_yt, x_max, speed, reverse, fhd
        Equation eq0(1, 0, -300, 1, 0.23f, MIN, 35, true, fhd);
        Movement mvmt0(1280, fhd);
        mvmt0.push_back(eq0);
        Entity me0(mvmt0, textures["entity0"]); //top right, fast
        me0.setScale(0.07f, 0.07f);
        em_front.spawn(me0);

        Equation eq1(0, 0, -300, 0, 0, MAX, 8, false, fhd);
        Movement mvmt1(-135, fhd);
        mvmt1.push_back(eq1);
        Entity me1(mvmt1, textures["entity1"]); //mid left, lower
        me1.setScale(0.3f, 0.3f);
        em_back.spawn(me1);

        Equation eq3(0, 0, -450, 0, 0, MIN, 5, true, fhd);
        Movement mvmt3(1020, fhd);
        mvmt3.push_back(eq3);
        Entity me3(mvmt3, textures["entity3"]);
        me3.setScale(0.2f, 0.2f);
        em_back.spawn(me3); //bottom right, behind tower

        Equation eq5(0, 0, -175, 0, 0, MIN, 15, true, fhd);
        Movement mvmt5(1280, fhd);
        mvmt5.push_back(eq5);
        Entity me5(mvmt5, textures["entity5"]);
        me5.setScale(0.5f, 0.5f);
        em_front.spawn(me5); //top right, lower

        Equation eq6(0, 0, -400, 0, 0, MAX, 3, false, fhd);
        Movement mvmt6(200, fhd);
        mvmt6.push_back(eq6);
        Entity me6(mvmt6, textures["entity6"]);
        me6.setScale(0.1f, 0.1f);
        em_back.spawn(me6); //bottom left, behind tower

        em_flags[0] = true;
    }
    else if ((int)mem_time == 10 && em_flags[1] == false) {
        Equation eq2(0, 0, -260, 0, 0, MAX, 8, false, fhd);
        Movement mvmt2(-102, fhd);
        mvmt2.push_back(eq2);
        Entity me2(mvmt2, textures["entity2"]);
        me2.setScale(0.22f, 0.22f);
        em_back.spawn(me2); //mid left, upper

        Equation eq4(0, 0, -100, 0, 0, MIN, 15, true, fhd);
        Movement mvmt4(1278, fhd);
        mvmt4.push_back(eq4);
        Entity me4(mvmt4, textures["entity4"]);
        me4.setScale(0.5f, 0.5f);
        em_front.spawn(me4); //top right, higher

        em_flags[1] = true;
    }
    else if ((int)mem_time == 70 && em_flags[2] == false) {
        Equation eq7(1, 0, -400, 1, 0.1f, MIN, 35, true, fhd);
        Movement mvmt7(1280, fhd);
        mvmt7.push_back(eq7);
        Entity me7(mvmt7, textures["entity0"]); //mid left, fast
        me7.setScale(0.07f, 0.07f);
        em_front.setRotation(em_front.getSize() - 1, 20);
        em_front.spawn(me7);
        
        em_flags[2] = true;
    }
    else if ((int)mem_time == 140) {
        int mem_flags_size = sizeof(em_flags);
        for (int i = 0; i < mem_flags_size; i++) {
            em_flags[i] = false;
        }
        em_clock.restart();
    }

    float frame_time = frame_clock.getElapsedTime().asSeconds();
    frame_clock.restart();
    em_back.update(frame_time);
    em_front.update(frame_time);
}