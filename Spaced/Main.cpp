#include <SFML\Graphics.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Nebulon", sf::Style::Default);
    sf::RectangleShape player(sf::Vector2f(20.0f,20.0f));
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
                cout << "Closing" << endl;
                window.close();
                break;
            case sf::Event::Resized:
                cout << evnt.size.width << "x" << evnt.size.height << endl;
                break;
            case sf::Event::TextEntered:
                if(evnt.text.unicode < 128) {
                    cout << (char)evnt.text.unicode;
                }
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
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

    return 0;
}