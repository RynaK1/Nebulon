#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>

//global variables
const static int GO_MAIN_MENU = 0;
const static int GO_OPTIONS_MENU = 1;
const static int GO_GAMEPLAY = 2;
const static int GO_END = 3;
const static int GO_HIGHSCORE = 4;
const static int QUIT = -1;


inline bool buttonBounds(sf::Vector2i mousePos, sf::Text text) {
	sf::FloatRect bound = text.getGlobalBounds();
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}


inline bool buttonBounds(sf::Vector2i mousePos, sf::RectangleShape shape) {
	sf::FloatRect bound = shape.getGlobalBounds();
	bound.top -= 13;
	bound.height += 20;
	if (bound.contains((float)mousePos.x, (float)mousePos.y)) {
		return true;
	}
	return false;
}


inline void writeToFile(std::string value, std::string key) {

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

	//rewrite data to file
	std::ofstream outFile("data.txt");
	if (!outFile.is_open()) {
		std::cerr << "Could not open or create data file <outFile>" << std::endl;
		return void();
	}



	size_t size = data.size();
	for (int i = 0; i < size; i++) {
		//find and replace modified option
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


inline std::string readFromFile(std::string option) {
	std::ifstream inFile("data.txt");
	if (!inFile.is_open()) {
		std::cerr << "Could not open or create data file <readFromFile>" << std::endl;
		return "";
	}

	std::string buffer;
	std::string result;
	while (std::getline(inFile, buffer)) {
		if (buffer.find(option) != std::string::npos) {
			result = buffer.substr(buffer.find('=') + 1);
		}
	}

	std::cout << result << std::endl;

	inFile.close();
	return result;
}
//save volume info to file
//add other volume options
//work on implementing gameplay