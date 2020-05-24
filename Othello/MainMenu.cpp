#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu():Single("Single",300,250),Multiplayer("Multiplayer", 300, 400)
{
	//Prepare Offline, Online and Othello

	if (!this->font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error";
	}
	this->Othello.setFont(this->font);
	this->Othello.setString("Othello");
	this->Othello.setCharacterSize(72);
	this->Othello.setFillColor(sf::Color::Red);
	this->Othello.setStyle(sf::Text::Bold | sf::Text::Underlined);
	this->Othello.setPosition(275, 50);
}
void MainMenu::Display(sf::RenderWindow &window)		//We need to know what window we are using		Using window.draw
{
	window.clear();
	this->Single.draw(window);
	this->Multiplayer.draw(window);
	//this->Online.draw(window);
	window.draw(this->Othello);
	window.display();


	//Draw all the thing we need
}