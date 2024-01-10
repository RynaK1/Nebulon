#include "LiveEntities.h"


LiveEntities::LiveEntities(bool fhd) {
	background_size = 0;
	if (fhd) {
		boundary = sf::FloatRect(0, 0, 1920, 1080);
	}
	else {
		boundary = sf::FloatRect(0, 0, 1280, 720);
	}
}


void LiveEntities::updatePosition(float time) {
	for (int i = 0; i < background_size; i++) {
		background[i].update(time);
		// boundary check
		if (!boundary.intersects(background[i].getGlobalBounds())) {
			background.erase(background.begin() + i);
			background_size -= 1;
			i -= 1;
		}
	}
}


void LiveEntities::spawn(int type, Entity entity) {
	if (type == 0) {
		background.push_back(entity);
		background_size += 1;
	}
	else {
		std::cerr << "Invalid ID for type of entity <LiveEntities>" << std::endl;
	}
}

/*
void LiveEntities::spawn(int type, InGameEntity entity) {

}
*/


Entity LiveEntities::getBackground(int element) {
	return background[element];
}

int LiveEntities::getBackgroundSize() {
	return background_size;
}