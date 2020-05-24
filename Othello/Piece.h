#pragma once
#include <SFML/Graphics.hpp>
class Piece						//Maybe inherit something
{
private:
	int status;			//Black piece=1 or white piece=2, empty=0
	sf::CircleShape circle;
	sf::Vector2f position;
	int row;
	int col;
public:
	Piece();
	Piece(int status, int row, int col);
	void change_status(int new_status);
	void setPosition(int row, int col);						//This set row and column!
	void setPosition(const sf::Vector2f& pos);					//This set exactly position
	void draw(sf::RenderWindow& window);
};