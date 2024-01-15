#include "Gameplay.h"


Gameplay::Gameplay(sf::RenderWindow* window) {
    this->window = window;

    // audio
    sf::SoundBuffer sfx_bullet_bfr;
    sf::SoundBuffer sfx_death_bfr;
    if (!music.openFromFile("../Resources/Audio/gameplay_music.ogg") ||
        !sfx_bullet_bfr.loadFromFile("../Resources/Audio/sfx_laser.ogg") ||
        !sfx_death_bfr.loadFromFile("../Resources/Audio/sfx_enemy_hurt.ogg")) {
        std::cerr << "sfx file missing  <Gameplay>" << std::endl;
    }

    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    music.play();
    sound["bullet"].setBuffer(sfx_bullet_bfr);
    sound["bullet"].setVolume(sounds.y);
    sound["death"].setBuffer(sfx_death_bfr);
    sound["death"].setVolume(sounds.y);

    //text font
    if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }

    //texts
    texts["stage"] = sf::Text("Stage " + std::to_string(1), font);
    texts["money"] = sf::Text(readFromFile("money"), font);
    texts["money"].setFillColor(sf::Color::White);

    //textures
    if (!textures["background"].loadFromFile("../Resources/Textures/BackgroundGame.png") ||
        !textures["backgroundFHD"].loadFromFile("../Resources/Textures/BackgroundGame_FHD.png") || 
        !textures["player"].loadFromFile("../Resources/Textures/ship_sprite4.png", sf::IntRect(768, 32, 227, 171)) ||
        !textures["bullet1_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(125, 433, 141, 126)) ||
        !textures["bullet2_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(199, 47, 172, 160)) ||
        !textures["health_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(625, 852, 330, 109)) ||
        !textures["healthbar_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(676, 968, 246, 24)) ||
        !textures["money_UI"].loadFromFile("../Resources/Textures/Game_UI2.png", sf::IntRect(505, 746, 81, 79)) ||
        !textures["bullet1"].loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6)) ||
        !textures["bullet2"].loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 32, 5, 11)) ||
        !textures["enemy0"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(695, 515, 284, 118)) ||
        !textures["enemy1"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(707, 238, 256, 244)) ||
        !textures["enemy100"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(56, 56, 285, 188))) {
        std::cerr << "Texture load failure <Gameplay>" << std::endl;
    }

    UIsprites["background"].setTexture(textures["background"]);
    UIsprites["bullet1"].setTexture(textures["bullet1_UI"]);
    UIsprites["bullet2"].setTexture(textures["bullet2_UI"]);
    UIsprites["health"].setTexture(textures["health_UI"]);
    UIsprites["healthbar"].setTexture(textures["healthbar_UI"]);
    UIsprites["money"].setTexture(textures["money_UI"]);

    //resolution
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        fhd = true;
        boundary = sf::FloatRect(0, 0, 1920, 1080);
    }
    else {
        fhd = false;
        boundary = sf::FloatRect(0, 0, 1280, 720);
    }

    money = stoi(readFromFile("money"));
    player = Player(textures["player"], 100);
    stage = Stage(textures);

    scaleUI();
    scaleEntities();
}


int Gameplay::display() {
    frame_clock.restart();
    //animation_clock.restart();
    while (window->isOpen()) {
        float time = frame_clock.getElapsedTime().asSeconds();
        frame_clock.restart();

        sf::Event evnt;
        while (window->pollEvent(evnt)) {
            if(evnt.type == sf::Event::Closed) {
                window->close();
                return QUIT;       
            }
        }   
        //player movement
        player.move(time);
        player.keepInBoundary(boundary);

        //enemy updates
        stage.spawn(&enemies);
        updateEntityPosition(time);

        //entity collision updates

        //stage text animation
        stageAnimation();

        ///////////////////////// FIGURE OUT DIFFERENT WAY TO STORE ENTITIES TO CONTAIN ALL CLASSES


        time = frame_clock.restart().asSeconds();

        //draw updated graphics
        window->clear();
        window->draw(UIsprites["background"]);

        size_t entities_size = enemies.size();
        for (int i = 0; i < entities_size; i++) {
            window->draw(enemies[i]->getSprite());
        }


        window->draw(player.getSprite());
        window->draw(UIsprites["health_UI"]);
        UIsprites["healthbar_UI"].setTextureRect(sf::IntRect(676, 968, 246 * player.getHealth() / 100, 24));
        window->draw(UIsprites["healthbar_UI"]);
        window->draw(texts["money"]);
        window->draw(UIsprites["money_UI"]);
        window->draw(texts["stage"]);
        window->display();
    }
    return QUIT;
}


void Gameplay::updateCollisions() {

}

void Gameplay::scaleUI() {
    float scale;
    if (fhd) {
        scale = 1.5f;
        UIsprites["background"].setTexture(textures["backgroundFHD"]);
    }
    else {
        scale = 1;
        UIsprites["background"].setTexture(textures["background"]);
    }

    UIsprites["bullet1_UI"].setScale(0.41f * scale, 0.41f * scale);
    UIsprites["bullet2_UI"].setScale(0.335f * scale, 0.335f * scale);
    UIsprites["health_UI"].setScale(0.65f * scale, 0.65f * scale);
    UIsprites["healthbar_UI"].setScale(0.65f * scale, 0.65f * scale);
    UIsprites["money_UI"].setScale(0.4f * scale, 0.4f * scale);
    texts["money"].setCharacterSize((unsigned)(23 * scale));
    texts["stage"].setCharacterSize((unsigned)(40 * scale));

    UIsprites["bullet1_UI"].setPosition(905 * scale, 645 * scale);
    UIsprites["bullet2_UI"].setPosition(970 * scale, 645 * scale);
    UIsprites["health_UI"].setPosition(1050 * scale, 635 * scale);
    UIsprites["healthbar_UI"].setPosition(1080 * scale, 662 * scale);
    texts["money"].setPosition(((1280 * scale) - texts["money"].getLocalBounds().width) / 1.017f,
                               ((720 * scale) - texts["money"].getLocalBounds().height) / 50);
    UIsprites["money_UI"].setPosition(texts["money"].getGlobalBounds().left - (45 * scale),
                                     ((720 * scale) - texts["money"].getLocalBounds().height) / 55);
    texts["stage"].setPosition(((1280 * scale) - texts["stage"].getLocalBounds().width) / 2,
                               ((720 * scale) - texts["stage"].getLocalBounds().height) / 3.5f);
}

void Gameplay::scaleEntities() {
    if (fhd) {
        player.setScale(0.375f, 0.375f);
    }
    else {
        player.setScale(0.25f, 0.25f);
    }
}

void Gameplay::updateEntityPosition(float time) {
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->update(time);
        //bounds check
        sf::FloatRect pos = enemies[i]->getGlobalBounds();
        if (!boundary.intersects(pos)) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
        }
    }
}

void Gameplay::stageAnimation() {
    float time = animation_clock.getElapsedTime().asSeconds();
    if (time <= 0.5f) {
        texts["stage"].setFillColor(sf::Color(255, 255, 255, (uint8_t)(time * 510)));
    }
    else if (time >= 1.5 && time <= 2) {
        texts["stage"].setFillColor(sf::Color(255, 255, 255, (uint8_t)((2 - time) * 510)));
    }
}