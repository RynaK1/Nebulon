#include "Menu.h"

void Menu::display() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Nebulon", sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(20.0f, 20.0f));
    player.setFillColor(sf::Color::Cyan);
    player.setOrigin(sf::Vector2f(10.0f, 10.0f));
    sf::Texture playerTexture;

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
            case sf::Event::TextEntered:
                if (evnt.text.unicode < 128) {
                    std::cout << (char)evnt.text.unicode;
                }
            }
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