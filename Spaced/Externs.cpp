#include "Externs.h"

/*
* calcVolPercent
*
* Description: Calculates the position of the volume knob with respect to the volume bar
*			   and takes into account the space between the edge of the window and volume 
			   bar. Result is divided by the length of the volume bar length to get a
			   percentage.
* Parameters: int knob_pos: x-coordinate pixel position of the volume knob
*			  float window_x: x-axis width of the window
*/
float calcVolPercent(float knob_pos, float offset) {
	return std::round((knob_pos - offset) / 2.3f);
}

/*
* Description: Translates the integer volume percentage into a string then removes excess
*			   numbers and adds a percentage symbol.
*/
std::string getVolPercentString(float num) {
	std::string main_vol = std::to_string(num);
	main_vol = main_vol.substr(0, main_vol.find('.'));
	main_vol.append("%");
	return main_vol;
}


/*
* buttonBounds
*
* Description: Checks if the mouse position is within the boundaries of a texture using
			   the contains method.
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
* Description: Checks if the mouse position is within the boundaries of a texture using
			   the contains method.
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
* Description: Grabs data from the file before emptying it and rewriting the values back to
			   to the file. A particular value is changed for the wanted key while
			   rewriting.
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
			outFile << option + "=" + value << std::endl;
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
* Description: Reads through the file until the wanted key is found. The value of the key
*			   is then returned.
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
			break;
		}
	}
	inFile.close();
	return result;
}