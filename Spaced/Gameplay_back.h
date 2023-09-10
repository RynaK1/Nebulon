#pragma once

#include <SFML\Graphics.hpp>

sf::Vector2f getMoveVector(sf::Event evnt, float mvmt_speed);
bool checkPlayerBounds();