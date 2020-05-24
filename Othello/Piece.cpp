#include "Piece.h"




Piece::Piece() :circle(27.5), status(0), row(0), col(0)
{
	this->position.y = this->row*62.5 + 15 + 3.25;
	this->position.x = this->col*62.5 + 50 + 3.25;
	this->circle.setPosition(this->position);
}
Piece::Piece(int statusx, int rowx, int colx):circle(27.5),status(statusx),row(rowx),col(colx)
{
	this->position.y = this->row*62.5 +15+3.25;
	this->position.x = this->col*62.5 + 50+3.25;
	this->circle.setPosition(this->position);
}
void Piece::change_status(int new_status)
{
	this->status = new_status;
}
void Piece::setPosition(int row, int col)					//This set row and column!
{
	this->row = row;
	this->col = col;
	this->position.y = this->row*62.5 + 31.25 + 15;
	this->position.x = this->col*62.5 + 31.25 + 50;
	this->circle.setPosition(this->position);
}

void Piece::setPosition(const sf::Vector2f& pos)					//This set exactly position
{
	this->position = pos;
	this->circle.setPosition(this->position);
}



void Piece::draw(sf::RenderWindow& window)
{
	if (status == 2)
	{
		window.draw(this->circle);
	}
	if (status == 1)
	{
		window.draw(this->circle);
		sf::CircleShape circlex(26.f);
		circlex.setFillColor(sf::Color::Black);
		circlex.setPosition(this->position.x+1.5,this->position.y+1.5);
		window.draw(circlex);
	}
}