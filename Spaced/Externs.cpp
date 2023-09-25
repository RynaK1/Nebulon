#include "Externs.h"

Equation::Equation() {
	pt = 0;
	xt = 0;
	yt = 0;
	m_xt = 0;
	m_yt = 0;
	x = 0;
	reverse = false;
}


Equation::Equation(float pt, float xt, float yt, float m_xt, float m_yt, float x, bool reverse) {
	this->pt = pt;
	this->xt = xt;
	this->yt = yt;
	this->m_xt = m_xt;
	this->m_yt = m_yt;
	this->x = x;
	this->reverse = reverse;
}


float calcVolPercent(float knob_pos, float offset) {
	return std::round((knob_pos - offset) / 2.3f);
}


sf::Vector2f calcVolTotal() {
	float main = stof(readFromFile("main_volume"));
	float x = (main / 100) * stof(readFromFile("music_volume"));
	float y = (main / 100) * stof(readFromFile("sfx_volume"));
	
	return sf::Vector2f(x, y);
}


std::string getVolPercentString(float percent) {
	std::string main_vol = std::to_string(percent);
	main_vol = main_vol.substr(0, main_vol.find('.'));
	main_vol.append("%");
	return main_vol;
}


bool buttonBounds(sf::Vector2i mousePos, sf::Text text) {
	sf::FloatRect bound = text.getGlobalBounds();
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}


bool buttonBounds(sf::Vector2i mousePos, sf::RectangleShape shape) {
	sf::FloatRect bound = shape.getGlobalBounds();
	bound.top -= 13;
	bound.height += 20;
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}


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