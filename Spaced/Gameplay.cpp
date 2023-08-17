#include "Gameplay.h"

int Gameplay::display(sf::RenderWindow &window) {
    sf::RectangleShape player(sf::Vector2f(20.0f, 20.0f));
    player.setFillColor(sf::Color::Cyan);
    player.setOrigin(sf::Vector2f(10.0f, 10.0f));

    player.setPosition(10.0f, 10.0f);
    window.draw(player);

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            switch (evnt.type) {

            case sf::Event::Closed:
                std::cout << "Closing" << std::endl;
                window.close();
                break;
            case sf::Event::Resized:
                std::cout << evnt.size.width << "x" << evnt.size.height << std::endl;
                break;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
                player.move(-0.1f, 0.0f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
                player.move(0.1f, 0.0f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                player.move(0.0f, -0.1f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
                player.move(0.0f, 0.1f);
            }

            window.clear();
            window.draw(player);
            window.display();
        }
    }
    return 1;
}