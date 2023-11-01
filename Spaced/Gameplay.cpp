#include "Gameplay.h"

Gameplay::Gameplay() {
    if (!font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf")) {
        std::cerr << "Could not load font" << std::endl;
    }

    int win_x = 1280;
    int win_y = 720;
    if (fhd) {
        win_x = 1920;
        win_y = 1080;
    }

    money = stoi(readFromFile("money"));

    fhd = false;
    bossDeath = false;
    stage_num = 1;

    if (!background_t.loadFromFile("../Resources/Textures/BackgroundGame.png") ||
        !backgroundFHD_t.loadFromFile("../Resources/Textures/BackgroundGame_FHD.png")) {
        std::cerr << "BackgroundGame(_FHD).png file missing" << std::endl;
    }
    if (!player_t.loadFromFile("../Resources/Textures/ship_sprite4.png", sf::IntRect(768, 32, 227, 171))) {
        std::cerr << "ship_sprite.png file missing" << std::endl;
    }
    if (!atk1_t.loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(125, 433, 141, 126)) ||
        !atk2_t.loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(199, 47, 172, 160)) ||
        !health_t.loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(625, 852, 330, 109)) ||
        !healthbar_t.loadFromFile("../Resources/Textures/Game_UI.png", sf::IntRect(676, 968, 246, 24))) {
        std::cerr << "Game_UI.png file missing" << std::endl;
    }

    if (!moneyc_t.loadFromFile("../Resources/Textures/Game_UI2.png", sf::IntRect(505, 746, 81, 79))) {
        std::cerr << "Game_UI2.png file missing" << std::endl;
    }

    atk1.setTexture(atk1_t);
    atk2.setTexture(atk2_t);
    health.setTexture(health_t);
    healthbar.setTexture(healthbar_t);
    moneyc.setTexture(moneyc_t);
}


int Gameplay::display(sf::RenderWindow& window) {
    //set resolution in case of res change
    fhd = false;
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        fhd = true;
    }

    //lives
    int lives = stoi(readFromFile("lives"));

    //set clock
    sf::Clock clock;
    float time{};

    // ****************** audio initializations ***********************
    sf::Vector2f sounds = calcVolTotal();

    sf::Music music;
    if (!music.openFromFile("../Resources/Audio/gameplay_music.ogg")) {
        std::cerr << "Gameplay music file missing" << std::endl;
    }
    music.setVolume(sounds.x);
    music.play();

    sf::SoundBuffer sfx_bullet_bfr;
    sf::Sound sfx_bullet;
    if (!sfx_bullet_bfr.loadFromFile("../Resources/Audio/sfx_laser.ogg")) {
        std::cerr << "sfx file missing" << std::endl;
    }
    sfx_bullet.setBuffer(sfx_bullet_bfr);
    sfx_bullet.setVolume(sounds.y);

    sf::SoundBuffer sfx_enemy_death_bfr;
    sf::Sound sfx_enemy_death;
    if (!sfx_enemy_death_bfr.loadFromFile("../Resources/Audio/sfx_enemy_hurt.ogg")) {
        std::cerr << "sfx file missing" << std::endl;
    }
    sfx_enemy_death.setBuffer(sfx_enemy_death_bfr);
    sfx_enemy_death.setVolume(sounds.y);

 
    // ****************** graphic initializations ***********************
    // money UI
    money_txt = sf::Text(readFromFile("money"), font);
    money_txt.setFillColor(sf::Color::White);

    scaleUI();

    //player bullets
    sf::Texture bullet1_t;
    sf::Texture bullet2_t;
    if (!bullet1_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6)) || 
        !bullet2_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 32, 5, 11))) {
        std::cerr << "spaceSprites.png file missing" << std::endl;
    }

    //enemies
    sf::Texture textures[5];
    if (!textures[0].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(695, 515, 284, 118)) ||
        !textures[1].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(707, 238, 256, 244)) ||
        !textures[2].loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(56, 56, 285, 188))) {
        std::cerr << "ship_sprite5.png file missing" << std::endl;
    }

    EnemyManager enemyManager(fhd);
    stage = Stage(fhd, textures);
    player = Player(player_t, fhd);

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            if(evnt.type == sf::Event::Closed) {
                window.close();
                return QUIT;       
            }
        }   

        // player movement and boundary
        sf::FloatRect pos = player.getSprite().getGlobalBounds();
        std::array<bool, 4> bounds = checkPlayerBounds(pos, window.getSize());
        player.move(time, bounds);

        // spawns appropriate stage enemies at appropriate timing
        if (bossDeath == true) {
            stage_num += 1;
            bossDeath = false;
        }
        std::vector<Enemy> spwn = stage.spawn(stage_num);
        size_t spwn_size = spwn.size();
        for (size_t i = 0; i < spwn_size; i++) {
            enemyManager.spawn(spwn[i]);
        }

        // update entities
        player.updateBullets(time);
        enemyManager.update(time);

        std::array<bool, 2> death = updateCollisions(enemyManager, player);
        if (death[0] == true) { //player death
            writeToFile(std::to_string(money), "money");
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

        time = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            if (player.shoot(bullet1_t, 1)) {
                sfx_bullet.play();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            if (player.shoot(bullet2_t, 2)) {
                sfx_bullet.play();
            }
        }

        // draw updated graphics
        window.clear();
        window.draw(background);
        std::vector<Bullet> bullets = player.getBullets();
        size_t bullets_size = bullets.size();
        for (int i = 0; i < bullets_size; i++) {
            window.draw(bullets[i].getSprite());
        }
        int enemies_size = enemyManager.getEnemies_size();
        std::vector<Enemy> enemies = enemyManager.getEnemies();
        for (int i = 0; i < enemies_size; i++) {
            window.draw(enemies[i].getSprite());
        }
        window.draw(player.getSprite());

        atk1.setColor(sf::Color(255, 255, 255, (uint8_t)player.getCDPercent(1)));
        window.draw(atk1);
        atk2.setColor(sf::Color(255, 255, 255, (uint8_t)player.getCDPercent(2)));
        window.draw(atk2);

        window.draw(health);
        healthbar.setTextureRect(sf::IntRect(676, 968, 246 * player.getHealth() / 100, 24));
        window.draw(healthbar);
        window.draw(money_txt);
        window.draw(moneyc);
        window.display();
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

    std::vector<Enemy> enemies = em.getEnemies();
    sf::Sprite player_s = player.getSprite();
    size_t enemies_size = enemies.size();
    for (int i = 0; i < enemies_size; i++) {
        if (enemies[i].getGlobalBounds().intersects(player_s.getGlobalBounds()))
        {
            int health = player.getHealth() - 10;
            if (health <= 0) {
                death[0] = true;
            }
            else {
                player.playerDamaged(10);
            }
        }
    }

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
                    moneyc.setPosition(money_txt.getGlobalBounds().left - (45 * scale),
                        ((720 * scale) - money_txt.getLocalBounds().height) / 55);
                    if (typeid(em.getEnemy(i)).name() == typeid(EnemyBoss).name()) {
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
        background.setTexture(background_t);
    }
    else if (fhd) {
        scale = 1.5;
        background.setTexture(backgroundFHD_t);
    }
    atk1.setScale(0.41f * scale, 0.41f * scale);
    atk2.setScale(0.335f * scale, 0.335f * scale);
    health.setScale(0.65f * scale, 0.65f * scale); 
    healthbar.setScale(0.65f * scale, 0.65f * scale);
    moneyc.setScale(0.4f * scale, 0.4f * scale);
    money_txt.setCharacterSize((unsigned)(23 * scale));

    atk1.setPosition(905 * scale, 645 * scale);
    atk2.setPosition(970 * scale, 645 * scale);
    health.setPosition(1050 * scale, 635 * scale);
    healthbar.setPosition(1080 * scale, 662 * scale);
    money_txt.setPosition(((1280 *  scale) - money_txt.getLocalBounds().width) / 1.017f,
                          ((720 * scale) - money_txt.getLocalBounds().height) / 50);
    moneyc.setPosition(money_txt.getGlobalBounds().left - (45 * scale),
                      ((720 * scale) - money_txt.getLocalBounds().height) / 55);
}