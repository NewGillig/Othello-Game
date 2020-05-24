#pragma once
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
class Button
{
private:
	string text;
	sf::Text titleText;
	sf::Texture button;
	sf::Sprite buttonImage;
	sf::Font font;
	sf::Vector2f position;
public:
	Button(string textx,float x,float y);			//set text, size and so on.

	void draw(sf::RenderWindow& window);
};
