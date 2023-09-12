#include "Game.h"
#include "Gameplay.h"
#include "Player.h"

int Gameplay::display(sf::RenderWindow& window) {
    //sound
    sf::Music music;
    if (!music.openFromFile("../Resources/Audio/gameplay_music.ogg")) {
        std::cerr << "Gameplay music file missing" << std::endl;
    }

    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);

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

    window.draw(player.getSprite());

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {
            case sf::Event::Closed:
                window.close();
                return QUIT;
                break;
            }
        }        
        
        // player movement and boundary
        sf::FloatRect pos = player.getSprite().getGlobalBounds();
        std::array<bool, 4> bounds = game.checkPlayerBounds(pos, window.getSize());
        player.move(time, bounds);
        player.updateBullets(time);

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
        window.draw(player.getSprite());
        window.display();

    }
    return 1;
}