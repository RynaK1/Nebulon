#include "Highscore.h"

int Highscore::display(sf::RenderWindow& window, sf::Music& music) {
    sf::Texture bround;
    bround.loadFromFile("../Resources/Textures/spaceBackground.png");
    sf::Sprite background(bround);

    //texts and buttons
    sf::Font font;
    font.loadFromFile("../Resources/Textures/AlfaSlabOne-Regular.ttf"); 

    sf::Text hd("1920x1080", font);
    hd.setCharacterSize(30);
    hd.setStyle(sf::Text::Bold);
    hd.setFillColor(sf::Color::White);
    hd.setPosition(200, 400);

    sf::Text small("900x600", font);
    small.setCharacterSize(30);
    small.setStyle(sf::Text::Bold);
    small.setFillColor(sf::Color::White);
    small.setPosition(210, 460);

    sf::Text large("3840x2160", font);
    large.setCharacterSize(30);
    large.setStyle(sf::Text::Bold);
    large.setFillColor(sf::Color::White);
    large.setPosition(200, 520);

    while (window.isOpen()) {

        sf::Event evnt;
        while (window.pollEvent(evnt)) {

            if (evnt.type == sf::Event::Closed) {
                window.close();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {
                if (buttonBounds(mousePos, 200, 300, 400, 428)) {
                    hd.setFillColor(sf::Color::Red);
                    window.setSize({ 1920, 1080 });
                    //sf::View view_hd(sf::FloatRect(0, 0, 1000, 1000));
                    //window.setView(view_hd);
                }
            }
            else {
                hd.setFillColor(sf::Color::White);
            }
        }

        window.clear();
        window.draw(background);
        window.draw(small);
        window.draw(hd);
        window.draw(large);
        window.display();
    }

    return 1;
}