#pragma once
#include "Button.h"
#include "Text.h"
#include <SFML/Graphics.hpp>
class MainMenu
{
private:
	Button Single;
	Button Multiplayer;
	//Button Online;
	sf::Text Othello;
	sf::Font font;
public:
	MainMenu();
	void Display(sf::RenderWindow &window);			//We need to know what window we are using		Using window.draw
};
