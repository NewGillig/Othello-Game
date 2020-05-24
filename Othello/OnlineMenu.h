#pragma once
#include "Button.h"
#include "Text.h"
#include <SFML/Graphics.hpp>

class OnlineMenu
{
private:
	//Button Offline;
	//Button Online;
	Textbox Key;
	sf::Font font;
public:
	OnlineMenu();
	void Display(sf::RenderWindow &window);			//We need to know what window we are using		Using window.draw
};
