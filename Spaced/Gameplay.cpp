#include "Gameplay.h"

int Gameplay::display(sf::RenderWindow& window) {
    //sound
    sf::Music music;
    if (!music.openFromFile("../Resources/Audio/gameplay_music.ogg")) {
        std::cerr << "Gameplay music file missing" << std::endl;
    }

    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    music.play();

    //set clock
    sf::Clock clock;
    float time{};
 
    // ****************** graphic initializations ***********************
    //background
    sf::Texture bround_t;
    if (!bround_t.loadFromFile("../Resources/Textures/spaceBackground.png")) {
        std::cerr << "spaceSprites.png file missing <background>" << std::endl;
    }
    sf::Sprite background(bround_t);

    //player
    sf::Texture player_t;
    if (!player_t.loadFromFile("../Resources/Textures/spaceSprites.png", sf::IntRect(0, 1, 31, 29))) {
        std::cerr << "spaceSprites.png file missing <player>" << std::endl;
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
                    eq.x = 431;
                    enemyManager.spawn(1, eq);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    Equation eq;
                    eq.pt = 2;
                    eq.xt = -25;
                    eq.yt = -650;
                    eq.m_xt = 0.05f;
                    eq.m_yt = 1.5f;
                    eq.x = 83;
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
                    enemyManager.spawn(3, eq);
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
        game.updateCollisions(enemyManager, player);

        time = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            player.shoot(bullet1_t, 1);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            player.shoot(bullet2_t, 2);
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

// IMPLEMENT ENEMY ATTACK
//OPTIMIZE CHECKS FOR HITS?
//      currently n^2 for enemy to bullet       