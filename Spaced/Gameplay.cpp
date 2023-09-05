#include "Gameplay.h"


int Gameplay::display(sf::RenderWindow& window, sf::Music& music) {

    // ****************** graphic initializations ***********************
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

        sf::Vector2f v;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            v.y -= 0.4f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            v.x -= 0.4f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            v.y += 0.4f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            v.x += 0.4f;
        }

        if (v.x != 0 && v.y != 0) {
            v /= std::sqrt(2.0f);
        }

        

        player.move(v);
        
        window.clear();
        window.draw(background);
        window.draw(player);
        window.display();
    }
    return 1;
}