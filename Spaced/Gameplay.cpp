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
                    eq.pwr = 3;
                    eq.horiz = -150;
                    eq.vert = -350;
                    eq.mult_vert = 0.005f;
                    eq.mult_horiz = 0.25f;
                    eq.x = 431;
                    enemyManager.spawn(1, eq);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    Equation eq;
                    eq.pwr = 2;
                    eq.horiz = -25;
                    eq.vert = -650;
                    eq.mult_vert = 1.5f;
                    eq.mult_horiz = 0.05f;
                    eq.x = 83;
                    enemyManager.spawn(2, eq);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    Equation eq;
                    eq.pwr = 0;
                    eq.horiz = 0;
                    eq.vert = -200;
                    eq.mult_vert = 0;
                    eq.mult_horiz = 0;
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