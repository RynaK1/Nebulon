#pragma once

#include<vector>

#include "Entity.h"


class LiveEntities {
private:
	sf::FloatRect boundary;
	int background_size;
	std::vector<Entity> background;
public:
	LiveEntities() : background_size(0) {}
	LiveEntities(bool fhd);
	void updatePosition(float time);
	void spawn(int type, Entity entity);
	//void spawn(int type, InGameEntity entity);
	Entity getBackground(int element);
	int getBackgroundSize();
};