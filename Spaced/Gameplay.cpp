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
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    Game game;
    Player player;
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
        player.updateBullets(time);
        enemyManager.updateEnemies(time);

        time = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Space)) {
            player.shoot();
        }

        // check collisions
        if (game.checkPlayerCollision(player, enemyManager)) {
            // IMPLEMENT PLAYER TO ENEMY COLLISION
        }

        std::vector<Enemy> es = enemyManager.getEnemies();
        int enemyManager_size = enemyManager.getEnemies_size();
        for (int i = 0; i < enemyManager_size; i++) {
            if (game.checkEnemyCollision(es[i], player.getBulletManager())) {
                // IMPLEMENT ENEMY TO BULLET COLLISION
            }
        }
   
        window.clear();
        window.draw(background);

        int bullets_size = player.getBulletManager().getBullets_size();
        std::vector<sf::Sprite> bs = player.getBulletManager().getBullets();
        for (int i = 0; i < bullets_size; i++) {
            window.draw(bs[i]);
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


// IMPLEMENT HEALTH
//OPTIMIZE CHECKS FOR HITS
//      currently n^2 for enemy to bullet       