#include "Gameplay.h"

int Gameplay::display(sf::RenderWindow& window) {
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

    //player
    sf::Texture player_t;
    if (!player_t.loadFromFile("../Resources/Textures/ship_sprite4.png", sf::IntRect(768, 32, 227, 171))) {
        std::cerr << "ship_sprite.png file missing <player>" << std::endl;
    }

    //player bullets
    sf::Texture bullet1_t;
    if (!bullet1_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(7, 32, 3, 6))) {
        std::cerr << "spaceSprites.png file missing" << std::endl;
    }

    sf::Texture bullet2_t;
    if (!bullet2_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 32, 5, 11))) {
        std::cerr << "spaceSprites.png file missing" << std::endl;
    }

    Game game;
    Player player(player_t);
    EnemyManager enemyManager;

    window.draw(player.getSprite());

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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                    Equation eq;
                    eq.pt = 3;
                    eq.xt = -150;
                    eq.yt = -350;
                    eq.m_xt = 0.25f;
                    eq.m_yt = 0.005f;
                    eq.x = 432;
                    if (win_x == 1920) {
                        eq.x = 680;
                    }

                    enemyManager.spawn(1, eq);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    Equation eq;
                    eq.pt = 2;
                    eq.xt = -25;
                    eq.yt = -650;
                    eq.m_xt = 0.05f;
                    eq.m_yt = 1.5f;
                    eq.x = 84;
                    if (win_x == 1920) {
                        eq.x = 126;
                    }

                    enemyManager.spawn(2, eq);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    Equation eq;
                    eq.pt = 0;
                    eq.xt = 0;
                    eq.yt = -200;
                    eq.m_xt = 0;
                    eq.m_yt = 0;
                    eq.x = -60;
                    enemyManager.spawn(10, eq);
                }
            }

        }        
        
        // player movement and boundary
        sf::FloatRect pos = player.getSprite().getGlobalBounds();
        std::array<bool, 4> bounds = game.checkPlayerBounds(pos, window.getSize());
        player.move(time, bounds);

        // update entities
        player.updateBullets(time);
        enemyManager.updateEnemies(time);
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
        std::vector<Enemy> enmies = enemyManager.getEnemies();
        for (int i = 0; i < enemies_size; i++) {
            window.draw(enmies[i].getSprite());
        }

        window.draw(player.getSprite());
        window.display();

    }
    return 1;
}

// scale enemy movement for resolution
// enemy movement in the -x direction
// create class for moving objects in background