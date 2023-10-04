#include "Gameplay.h"

Gameplay::Gameplay() {
    fhd = false;
    enemyManager = EnemyManager(fhd);

    if (!player_t.loadFromFile("../Resources/Textures/ship_sprite4.png", sf::IntRect(768, 32, 227, 171))) {
        std::cerr << "ship_sprite.png file missing <player>" << std::endl;
    }
    player = Player(player_t);
}

int Gameplay::display(sf::RenderWindow& window) {
    fhd = false;
    if (readFromFile("resolution").compare("1920x1080") == 0) {
        fhd = true;
    }
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
    //background
    float win_x = (float)window.getSize().x;
    float win_y = (float)window.getSize().y;

    sf::Texture bround;
    if (win_x == 1920) {
        bround.loadFromFile("../Resources/Textures/BackgroundGame_FHD.png");
    }
    else if (win_x == 1280) {
        bround.loadFromFile("../Resources/Textures/BackgroundGame.png");
    }
    sf::Sprite background(bround);

    //player bullets
    sf::Texture bullet1_t;
    sf::Texture bullet2_t;
    if (!bullet1_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6)) || 
        !bullet2_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 32, 5, 11))) {
        std::cerr << "spaceSprites.png file missing" << std::endl;
    }

    //enemies
    sf::Texture enemy0_t;
    sf::Texture enemy1_t;
    sf::Texture enemyBoss_t;
    if (!enemy0_t.loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(695, 515, 284, 118)) ||
        !enemy1_t.loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(707, 238, 256, 244)) ||
        !enemyBoss_t.loadFromFile("../Resources/Textures/ship_sprite5.png", sf::IntRect(56, 56, 285, 188))) {
        std::cerr << "ship_sprite5.png file missing" << std::endl;
    }

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                return QUIT;
                break;
            // TESTING FOR ENEMY SPAWN <===================================================
            case sf::Event::KeyPressed:
                float MAX = 9999;
                float MIN = -1000;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    Equation eq0(3, -150, -350, 0.25f, 0.005f, MIN, 70, true, fhd);
                    Movement mvmt0(764.5f, fhd);
                    mvmt0.push_back(eq0);
                    enemyManager.spawn(mvmt0, enemy0_t, 0, time);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    Equation eq1(2, -25, -650, 0.05f, 1.5f, MAX, 60, false, fhd);
                    Movement mvmt1(84, fhd);
                    mvmt1.push_back(eq1);
                    enemyManager.spawn(mvmt1, enemy1_t, 1, time);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    Equation eq2(0, 0, -200, 0, 0, MAX, 40, false, fhd);
                    Movement mvmt2(-60, fhd);
                    mvmt2.push_back(eq2);
                    enemyManager.spawn(mvmt2, enemyBoss_t, 10, time);
                }
            }

        }        
        
        // player movement and boundary
        sf::FloatRect pos = player.getSprite().getGlobalBounds();
        std::array<bool, 4> bounds = game.checkPlayerBounds(pos, window.getSize());
        player.move(time, bounds);

        // update entities
        player.updateBullets(time);
        enemyManager.update(time);
        std::array<bool, 2> death = game.updateCollisions(enemyManager, player);
        if (death[0] == true) { //check player death
            return GO_END;
        }
        if (death[1] == true) {
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
        window.display();

    }
    return QUIT;
}