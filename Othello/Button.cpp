#include "Button.h"

Button::Button(string textx,float x,float y)		//set text, size and so on.
{
	this->text = textx;
	this->button.loadFromFile("button.png");
	this->buttonImage.setTexture(button);
	if (!font.loadFromFile("arial.ttf"))
	{
		exit(-1);
	}
	this->titleText.setFont(font);
	this->titleText.setString(this->text);
	this->titleText.setCharacterSize(30);
	this->titleText.setFillColor(sf::Color::Black);
	this->titleText.setStyle(sf::Text::Bold);
	this->position.x = x;
	this->position.y = y;
}


void Button::draw(sf::RenderWindow& window)
{
	this->buttonImage.setPosition(this->position);
	this->titleText.setPosition(this->position.x+25,this->position.y+5);
	window.draw(this->buttonImage);
	window.draw(this->titleText);
}


