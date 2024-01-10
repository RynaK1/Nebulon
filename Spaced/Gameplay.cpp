#include "Gameplay.h"

/*
Gameplay::Gameplay(sf::RenderWindow* window) {
    this->window = window;

    money = stoi(readFromFile("money"));
    bossDeath = false;
    animation_flag = false;
    stage_num = 1;

    // audio
    if (!music.openFromFile("../Resources/Audio/gameplay_music.ogg") ||
        !sfx_bullet_bfr.loadFromFile("../Resources/Audio/sfx_laser.ogg") ||
        !sfx_enemy_death_bfr.loadFromFile("../Resources/Audio/sfx_enemy_hurt.ogg")) {
        std::cerr << "sfx file missing  <Gameplay>" << std::endl;
    }

    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    music.play();
    sfx_bullet.setBuffer(sfx_bullet_bfr);
    sfx_bullet.setVolume(sounds.y);
    sfx_enemy_death.setBuffer(sfx_enemy_death_bfr);
    sfx_enemy_death.setVolume(sounds.y);

    //text font
    if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }

    //texts
    stage_txt = sf::Text("Stage " + std::to_string(stage_num), font);
    money_txt = sf::Text(readFromFile("money"), font);
    money_txt.setFillColor(sf::Color::White);

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
        !textures["enemyBoss"].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(56, 56, 285, 188))) {
        std::cerr << "Texture load failure <Gameplay>" << std::endl;
    }

    bullet1_UI.setTexture(textures["bullet1_UI"]);
    bullet2_UI.setTexture(textures["bullet2_UI"]);
    health_UI.setTexture(textures["health_UI"]);
    healthbar_UI.setTexture(textures["healthbar_UI"]);
    money_UI.setTexture(textures["money_UI"]);

    //resolution
    fhd = false;
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        fhd = true;
    }
    scaleUI();

    stage = Stage(&textures, fhd);
    player = Player(textures["player"], fhd);
    enemyManager = EnemyManager(fhd);
}


int Gameplay::display() {
    frame_clock.restart();
    animation_clock.restart();
    animation_flag = true;
    stage.load(stage_num);
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
        // player movement and boundary
        sf::FloatRect pos = player.getSprite().getGlobalBounds();
        std::array<bool, 4> bounds = checkPlayerBounds(pos, window->getSize());
        player.move(time, bounds);

        // spawns appropriate stage enemies at appropriate timing
        if (bossDeath == true) {
            stage_num += 1;
            stage_txt.setString("Stage " + std::to_string(stage_num));
            stage.reset();
            stage.load(stage_num);
            animation_clock.restart();
            animation_flag = true;
            bossDeath = false;
        }
        
        stage.spawn(stage_num);

        // update entities
        player.updateBullets(time);
        enemyManager.update(time, textures["bullet1"]);

        std::array<bool, 2> death = updateCollisions(enemyManager, player);
        if (death[0] == true) { //player death
            writeToFile(std::to_string(money), "money");
            int lives = stoi(readFromFile("lives"));
            if (lives - 1 == 0) {
                writeToFile(std::to_string(10), "lives");
                return GO_GAMEOVER;
            }
            else {
                writeToFile(std::to_string(lives - 1), "lives");
                return GO_END;
            }
        }
        if (death[1] == true) { //enemy death
            sfx_enemy_death.play();
        }

        time = frame_clock.restart().asSeconds();

        // player shoot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if (player.shoot(textures["bullet1"], 1)) {
                sfx_bullet.play();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if (player.shoot(textures["bullet2"], 2)) {
                sfx_bullet.play();
            }
        }

        // next stage animation
        if (animation_flag) {
            stageAnimation();
        }
        if (animation_flag && animation_clock.getElapsedTime().asSeconds() >= 2) {
            animation_flag = false;
        }

        // draw updated graphics
        window->clear();
        window->draw(background);
        std::vector<Bullet> pbullets = player.getBullets();
        size_t pbullets_size = pbullets.size();
        for (int i = 0; i < pbullets_size; i++) {
            window->draw(pbullets[i].getSprite());
        }
        int enemies_size = enemyManager.getEnemies_size();
        std::vector<Enemy> enemies = enemyManager.getEnemies();
        for (int i = 0; i < enemies_size; i++) {
            window->draw(enemies[i].getSprite());
    
            std::vector<Bullet> ebullets = enemies[i].getBulletManager()->getBullets();
            size_t ebullets_size = ebullets.size();
            for (int j = 0; j < ebullets_size; j++) {
                window->draw(ebullets[j].getSprite());
            }
        }
        window->draw(player.getSprite());
        bullet1_UI.setColor(sf::Color(255, 255, 255, (uint8_t)(player.getCDPercent(1) * 255)));
        window->draw(bullet1_UI);
        bullet2_UI.setColor(sf::Color(255, 255, 255, (uint8_t)(player.getCDPercent(2) * 255)));
        window->draw(bullet2_UI);
        window->draw(health_UI);
        healthbar_UI.setTextureRect(sf::IntRect(676, 968, 246 * player.getHealth() / 100, 24));
        window->draw(healthbar_UI);
        window->draw(money_txt);
        window->draw(money_UI);
        window->draw(stage_txt);
        window->display();
    }
    return QUIT;
}


std::array<bool, 4> Gameplay::checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size) {
    std::array<bool, 4> bounds = { true, true, true, true };

    if (pos.left <= 0) {
        bounds[0] = false;
    }
    if (pos.left + pos.width >= win_size.x) {
        bounds[1] = false;
    }
    if (pos.top <= 0) {
        bounds[2] = false;
    }
    if (pos.top + pos.height >= win_size.y) {
        bounds[3] = false;
    }

    return bounds;
}


std::array<bool, 2> Gameplay::updateCollisions(EnemyManager& em, Player& player) {
    float scale = 1;
    if (fhd) {
        scale = 1.5f;
    }

    std::array<bool, 2> death = { false, false };

    //player collision with enemies and enemy attacks
    std::vector<Enemy> enemies = em.getEnemies();
    sf::Sprite player_s = player.getSprite();
    size_t enemies_size = enemies.size();
    sf::FloatRect player_pos = player_s.getGlobalBounds();
    for (int i = 0; i < enemies_size; i++) {
        if (enemies[i].getGlobalBounds().intersects(player_pos)) {
            int health = player.getHealth() - 10;
            if (health <= 0) {
                death[0] = true;
            }
            else {
                player.playerDamaged(10);
            }
        }

        std::vector<Bullet> enemy_bullets = enemies[i].getBulletManager()->getBullets();
        size_t enemy_bullets_size = enemy_bullets.size();
        for (int j = 0; j < enemy_bullets_size; j++) {
            if (enemy_bullets[j].getGlobalBounds().intersects(player_pos)) {
                enemies[i].getBulletManager()->remove(j);
                player.playerDamaged(10);
            }
        }
    }

    //player collision with enemy attacks


    //enemy collisions with bullets
    for (int i = 0; i < enemies.size(); i++) {
        std::vector<Bullet> bullets = player.getBullets();
        for (int j = 0; j < bullets.size(); j++) {
            if (bullets[j].getGlobalBounds().intersects(enemies[i].getGlobalBounds())) {
                int health = enemies[i].getHealth() - bullets[j].getDamage();
                if (health <= 0) {
                    money += em.getEnemy(i).getValue();
                    money_txt.setString(std::to_string(money));
                    money_txt.setPosition(((1280 * scale) - money_txt.getLocalBounds().width) / 1.017f,
                        ((720 * scale) - money_txt.getLocalBounds().height) / 50);
                    money_UI.setPosition(money_txt.getGlobalBounds().left - (45 * scale),
                        ((720 * scale) - money_txt.getLocalBounds().height) / 55);
                    if (em.getEnemy(i).isBoss()) {
                        bossDeath = true;
                    }
                    em.remove(i);
                    death[1] = true;
                }
                else {
                    em.setEnemyHealth(health, i);
                }
                player.removeBullet(j);
            }
        }
    }

    return death;
}


void Gameplay::scaleUI() {
    float scale;
    background = sf::Sprite();
    if (!fhd) {
        scale = 1;
        background.setTexture(textures["background"]);
    }
    else if (fhd) {
        scale = 1.5;
        background.setTexture(textures["backgroundFHD"]);
    }
    bullet1_UI.setScale(0.41f * scale, 0.41f * scale);
    bullet2_UI.setScale(0.335f * scale, 0.335f * scale);
    health_UI.setScale(0.65f * scale, 0.65f * scale); 
    healthbar_UI.setScale(0.65f * scale, 0.65f * scale);
    money_UI.setScale(0.4f * scale, 0.4f * scale);
    money_txt.setCharacterSize((unsigned)(23 * scale));
    stage_txt.setCharacterSize((unsigned)(40 * scale));

    bullet1_UI.setPosition(905 * scale, 645 * scale);
    bullet2_UI.setPosition(970 * scale, 645 * scale);
    health_UI.setPosition(1050 * scale, 635 * scale);
    healthbar_UI.setPosition(1080 * scale, 662 * scale);
    money_txt.setPosition(((1280 *  scale) - money_txt.getLocalBounds().width) / 1.017f,
                          ((720 * scale) - money_txt.getLocalBounds().height) / 50);
    money_UI.setPosition(money_txt.getGlobalBounds().left - (45 * scale),
                      ((720 * scale) - money_txt.getLocalBounds().height) / 55);
    stage_txt.setPosition(((1280 * scale) - stage_txt.getLocalBounds().width) / 2,
        ((720 * scale) - stage_txt.getLocalBounds().height) / 3.5f);
}


void Gameplay::stageAnimation() {
    float time = animation_clock.getElapsedTime().asSeconds();
    if (time <= 0.5f) {
        stage_txt.setFillColor(sf::Color(255, 255, 255, (uint8_t)(time * 510)));
    }
    else if (time >= 1.5 && time <= 2) {
        stage_txt.setFillColor(sf::Color(255, 255, 255, (uint8_t)((2 - time) * 510)));
    }
}
*/