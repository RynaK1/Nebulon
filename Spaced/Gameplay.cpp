#include "Gameplay.h"


int Gameplay::display(sf::RenderWindow& window, sf::Music& music) {
    //background
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    //player
    sf::RectangleShape player(sf::Vector2f(20.0f, 20.0f));
    player.setFillColor(sf::Color::Cyan);
    player.setOrigin(sf::Vector2f(10.0f, 10.0f));

    player.setPosition(10.0f, 10.0f);
    window.draw(player);

    int moving = 0;

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
                return QUIT;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player.move(0.0f, -0.5f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            player.move(-0.5f, 0.0f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player.move(0.0f, 0.5f);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            player.move(0.5f, 0.0f);
        }

        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }
    return 1;
}