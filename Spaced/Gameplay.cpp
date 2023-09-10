#include "Gameplay.h"
#include "Player.h"

int Gameplay::display(sf::RenderWindow& window) {

    //sound
    sf::Music music;
    if (!music.openFromFile("../Resources/Audio/gameplay_music.ogg")) {
        std::cerr << "Gameplay music file missing" << std::endl;
    }
    sf::Music sfx;
    if (!sfx.openFromFile("../Resources/Audio/sfx_enemy_hurt.ogg")) {
        std::cerr << "Sfx enemy gameplay file missing" << std::endl;
    }

    sf::Vector2f sounds = calcVolTotal();
    music.setVolume(sounds.x);
    sfx.setVolume(sounds.y);

    music.play();

    //set clock
    sf::Clock clock;
    float time{};
 
    // ****************** graphic initializations ***********************
    //background
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    //player
    Player player;

    window.draw(player.getSprite());

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
                return QUIT;
            } 
        }        

        player.move(time);
        if (checkPlayerBounds()) {

        }
        
        window.clear();
        window.draw(background);
        window.draw(player.getSprite());
        window.display();

        time = clock.restart().asSeconds();
    }
    return 1;
}