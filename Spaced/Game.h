#pragma once

#include <SFML\Graphics.hpp>
#include<array>

class Game {
private:
public:
	std::array<bool, 4> checkPlayerBounds(sf::FloatRect pos, sf::Vector2u win_size);
};