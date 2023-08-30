#include "Externs.h"

/*
* getVolumePercentage
*
* Description: Calculates the volume with respect to the pixel position of the volume bar.
* Parameters: int knob_pos: x-coordinate pixel position of the volume knob
*			  int window_x: x-axis width of the window
*/
int getVolumePercentage(int knob_pos, int window_x) {
	int vol_bar_width = 290;
	int left_gap = (window_x - vol_bar_width) / 2;
	return std::round((knob_pos - left_gap) / 2.9);
}


/*
* buttonBounds
*
* Description: Checks if the mouse position is within the boundaries of a texture.
*			   (overloaded function specifically for sf::Text texture)
* Parameters: sf::Vector2i mousePos: position of the mouse
*			  sf::Text shape: the text with which to check the boundaries
*/
bool buttonBounds(sf::Vector2i mousePos, sf::Text text) {
	sf::FloatRect bound = text.getGlobalBounds();
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}


/*
* buttonBounds
*
* Description: Checks if the mouse position is within the boundaries of a texture.
*			   (overloaded function specifically for sf::RectangleShape texture)
* Parameters: sf::Vector2i mousePos: position of the mouse
*			  sf::RectangleShape shape: the shape with which to check the boundaries
*/
bool buttonBounds(sf::Vector2i mousePos, sf::RectangleShape shape) {
	sf::FloatRect bound = shape.getGlobalBounds();
	bound.top -= 13;
	bound.height += 20;
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}


/*
* writeToFile
*
* Description: Rewrites the data file while making a change to a particular option.
* Parameters: string value: the new wanted value of the particular option
*			  string key: the particular option
*/
void writeToFile(std::string value, std::string key) {

	//get data from file
	std::ifstream inFile("data.txt");
	if (!inFile.is_open()) {
		std::cerr << "Could not open or create data file <inFile>" << std::endl;
		return void();
	}

	std::vector<std::string> data;
	std::string buffer;

	while (std::getline(inFile, buffer)) {
		data.push_back(buffer);
	}
	inFile.close();

	//rewrite data to file while modifying selected option
	std::ofstream outFile("data.txt");
	if (!outFile.is_open()) {
		std::cerr << "Could not open or create data file <outFile>" << std::endl;
		return void();
	}

	size_t size = data.size();
	for (int i = 0; i < size; i++) {
		std::string option = data[i].substr(0, data[i].find('='));
		if (option.compare(key) == 0) {
			outFile << option + "=" + value;
		}
		else {
			outFile << data[i] << std::endl;
		}
	}
	outFile.close();
}


/*
* readFromFile
*
* Description: Reads the value of a particular option setting from the data file.
* Parameters: string key: the particular option
*/
std::string readFromFile(std::string key) {
	std::ifstream inFile("data.txt");
	if (!inFile.is_open()) {
		std::cerr << "Could not open or create data file <readFromFile>" << std::endl;
		return "";
	}

	std::string buffer;
	std::string result;
	while (std::getline(inFile, buffer)) {
		if (buffer.find(key) != std::string::npos) {
			result = buffer.substr(buffer.find('=') + 1);
		}
	}
	inFile.close();
	return result;
}