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

/*
* getVolumePercentage
* 
* Description: Calculates the volume with respect to the pixel position of the volume bar.
* Parameters: int knob_pos: x-coordinate pixel position of the volume knob
*			  int window_x: x-axis width of the window
*/
int getVolumePercentage(int knob_pos, int window_x);


/*
* buttonBounds
*
* Description: Checks if the mouse position is within the boundaries of a texture.
*			   (overloaded function specifically for sf::Text texture)
* Parameters: sf::Vector2i mousePos: position of the mouse
*			  sf::Text shape: the text with which to check the boundaries
*/
bool buttonBounds(sf::Vector2i mousePos, sf::Text text);


/*
* buttonBounds
* 
* Description: Checks if the mouse position is within the boundaries of a texture.
*			   (overloaded function specifically for sf::RectangleShape texture)
* Parameters: sf::Vector2i mousePos: position of the mouse
*			  sf::RectangleShape shape: the shape with which to check the boundaries
*/
bool buttonBounds(sf::Vector2i mousePos, sf::RectangleShape shape);


/*
* writeToFile
* 
* Description: Rewrites the data file while making a change to a particular option.
* Parameters: string value: the new wanted value of the particular option
*			  string key: the particular option
*/
void writeToFile(std::string value, std::string key);


/*
* readFromFile
* 
* Description: Reads the value of a particular option setting from the data file.
* Parameters: string key: the particular option 
*/
std::string readFromFile(std::string key);