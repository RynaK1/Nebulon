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
    texts["stage"] = sf::Text("Stage 0", font);
    texts["money"] = sf::Text(readFromFile("money"), font);
    texts["money"].setFillColor(sf::Color::White);
    texts["boss_health"] = sf::Text("100", font);
    texts["boss_health"].setFillColor(sf::Color::White);

    //textures
    if (!textures["background"].loadFromFile("../Resources/Textures/BackgroundGame.png") ||
        !textures["player"].loadFromFile("../Resources/Textures/ship_sprite4.png", sf::IntRect(768, 32, 227, 171)) ||
        !textures["bullet0_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(125, 433, 141, 126)) ||
        !textures["bullet1_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(199, 47, 172, 160)) ||
        !textures["health_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(625, 852, 330, 109)) ||
        !textures["healthbar_UI"].loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(676, 968, 246, 24)) ||
        !textures["money_UI"].loadFromFile("../Resources/Textures/Game_UI2.png", sf::IntRect(505, 746, 81, 79)) ||
        !textures["bullet0"].loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6)) ||
        !textures["bullet1"].loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 32, 5, 11)) ||
        !textures["enemy0"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(695, 515, 284, 118)) ||
        !textures["enemy1"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(707, 238, 256, 244)) ||
        !textures["enemy100"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(56, 56, 285, 188))) {
        std::cerr << "Texture load failure <Gameplay>" << std::endl;
    }

    UIsprites["bullet0_UI"].setTexture(textures["bullet0_UI"]);
    UIsprites["bullet1UI"].setTexture(textures["bullet1_UI"]);
    UIsprites["health_UI"].setTexture(textures["health_UI"]);
    UIsprites["healthbar_UI"].setTexture(textures["healthbar_UI"]);
    UIsprites["money_UI"].setTexture(textures["money_UI"]);
    UIsprites["background"].setTexture(textures["background"]);
    UIsprites["boss_healthbar_UI"].setTexture(textures["healthbar_UI"]);

    boundary = sf::FloatRect(0, 0, 1280, 720);
    player = Player(textures["player"], sf::Vector2f(640, 500), 400, 100);

    money = stoi(readFromFile("money"));
    stage = Stage(textures);
    startNextStage();

    loadUI();
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
        player.attack(textures, &player_bullets);

        //entity updates
        stage.spawn(&enemies);
        for (Enemy* enemy : enemies) {
            enemy->attack(textures, &enemy_bullets);
        }
        updateEntityPosition(time);
        updateEntityCollision();

        //stage text animation
        stageAnimation();

        //player death
        if (player.getHealth() <= 0) {
            int num_lives = stoi(readFromFile("lives"));
            if (num_lives > 1) {
                num_lives -= 1;
                writeToFile(std::to_string(num_lives), "lives");
                return GO_END;
            }
            else {
                writeToFile("10", "lives");
                return GO_GAMEOVER;
            }
        }

        time = frame_clock.restart().asSeconds();

        //draw updated graphics
        window->clear();
        window->draw(UIsprites["background"]);
        for (Enemy* enemy : enemies) {
            window->draw(enemy->getSprite());
        }
        for (GameEntity* pb: player_bullets) {
            window->draw(pb->getSprite());
        }
        for (GameEntity* eb : enemy_bullets) {
            window->draw(eb->getSprite());
        }
        window->draw(player.getSprite());
        window->draw(UIsprites["health_UI"]);
        UIsprites["healthbar_UI"].setTextureRect(sf::IntRect(676, 968, 246 * player.getHealth() / 100, 24));
        window->draw(UIsprites["healthbar_UI"]);
        if (!enemies.empty()) {
            if (enemies[0]->getIsBoss()) {
                UIsprites["boss_healthbar_UI"].setTextureRect(sf::IntRect(676, 968, 246 * enemies[0]->getHealth() / 100, 24));
                texts["boss_health"].setString(std::to_string(enemies[0]->getHealth()));
            }
            else {
                UIsprites["boss_healthbar_UI"].setTextureRect(sf::IntRect(676, 968, 0, 24));
                texts["boss_health"].setString("0");
            }
        }
        window->draw(UIsprites["boss_healthbar_UI"]);
        window->draw(UIsprites["money_UI"]);
        window->draw(texts["boss_health"]);
        window->draw(texts["stage"]);
        window->draw(texts["money"]);
        window->display();
    }
    return QUIT;
}

void Gameplay::loadUI() {
    UIsprites["bullet0_UI"].setScale(0.41f, 0.41f);
    UIsprites["bullet1_UI"].setScale(0.335f, 0.335f);
    UIsprites["health_UI"].setScale(0.65f, 0.65f);
    UIsprites["healthbar_UI"].setScale(0.65f, 0.65f);
    UIsprites["money_UI"].setScale(0.4f, 0.4f);
    UIsprites["boss_healthbar_UI"].setScale(5.07f, 0.4f);
    texts["money"].setCharacterSize((unsigned)(23));
    texts["stage"].setCharacterSize((unsigned)(40));
    texts["boss_health"].setCharacterSize((unsigned)20);

    UIsprites["bullet0_UI"].setPosition(905, 645);
    UIsprites["bullet1_UI"].setPosition(970, 645);
    UIsprites["health_UI"].setPosition(1050, 635);
    UIsprites["healthbar_UI"].setPosition(1080, 662);
    texts["boss_health"].setPosition(620, 5);
    texts["money"].setPosition(1210, 30);
    UIsprites["money_UI"].setPosition(1170, 30);
    texts["stage"].setPosition((1280 - texts["stage"].getLocalBounds().width) / 2,
                               (720 - texts["stage"].getLocalBounds().height) / 3.5f);
    UIsprites["boss_healthbar_UI"].setPosition(15, 12);
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

    for (int i = 0; i < enemy_bullets.size(); i++) {
        enemy_bullets[i]->update(time);
        //bounds check
        sf::FloatRect pos = enemy_bullets[i]->getGlobalBounds();
        if (!boundary.intersects(pos)) {
            delete enemy_bullets[i];
            enemy_bullets.erase(enemy_bullets.begin() + i);
        }
    }

    for (int i = 0; i < player_bullets.size(); i++) {
        player_bullets[i]->update(time);
        //bounds check
        sf::FloatRect pos = player_bullets[i]->getGlobalBounds();
        if (!boundary.intersects(pos)) {
            delete player_bullets[i];
            player_bullets.erase(player_bullets.begin() + i);
        }
    }
}

void Gameplay::updateEntityCollision() {
    //enemy to player and player_bullets
    for (int i = 0; i < enemies.size(); i++) {
        //enemy hits player
        if (player.getGlobalBounds().intersects(enemies[i]->getGlobalBounds())) {
            player.hit(enemies[i]->getDmg());
        }

        for (int j = 0; j < player_bullets.size(); j++) {
            //player bullets hits enemy
            if (player_bullets[j]->getGlobalBounds().intersects(enemies[i]->getGlobalBounds())) {
                enemies[i]->hit(player_bullets[j]->getDmg());
                if (enemies[i]->getHealth() <= 0) {
                    if (enemies[i]->getIsBoss()) {
                        startNextStage();
                    }
                    delete enemies[i];
                    enemies.erase(enemies.begin() + i);
                }

                delete player_bullets[j];
                player_bullets.erase(player_bullets.begin() + j);
            }
        }
    }

    //enemy bullets hits player
    for (int i = 0; i < enemy_bullets.size(); i++) {
        if (player.getGlobalBounds().intersects(enemy_bullets[i]->getGlobalBounds())) {
            player.setHealth(player.getHealth() - enemy_bullets[i]->getDmg());
            delete enemy_bullets[i];
            enemy_bullets.erase(enemy_bullets.begin() + i);
        }
    }
}

void Gameplay::startNextStage() {
    stage.nextStage();
    texts["stage"].setString("Stage " + std::to_string(stage.getStage_num()));
    animation_clock.restart();
}

void Gameplay::stageAnimation() {
    float time = animation_clock.getElapsedTime().asSeconds();
    if (time <= 0.5f) {
        texts["stage"].setFillColor(sf::Color(255, 255, 255, (uint8_t)(time * 510)));
    }
    else if (time >= 1.5f && time <= 2) {
        texts["stage"].setFillColor(sf::Color(255, 255, 255, (uint8_t)((2 - time) * 510)));
    }
}


//2. UPGRADES
//3. SET UP KEY BINDINGS?
//4. SET UP TUTORIAL