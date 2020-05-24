#include "Game.h"
#include <Windows.h>
#include <iostream>
using namespace std;

Game::Game() : window(sf::VideoMode(800, 600), "Othello Game"),mode(0)
{}


void Game::Play()
{

	//Draw Main Menu
	mainmenu.Display(this->window);
	//window.display();


	while (window.isOpen())
	{
		sf::Event event;
		//All events are here
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				//If click, check mode
				if (this->mode == 0)					//check whether the mouse is in the button or cell of board and do anything
				{
					sf::Vector2i position;
					position=sf::Mouse::getPosition(window);
					cout << position.x << "," << position.y << endl;
					if (position.x > 300 && position.x < 500 && position.y>250 && position.y < 300)	//mouse is on Offline button.
					{
						this->mode = 2;
						this->board.init(true);
						this->board.Display(this->window);
					}
					if (position.x > 300 && position.x < 500 && position.y>400 && position.y < 450)	//mouse is on Offline button.
					{
						this->mode = 2;
						this->board.init(false);
						this->board.Display(this->window);
					}
				}
				else if(this->mode==1)
				{ }
				else if (this->mode == 2)
				{
					sf::Vector2i position;
					position = sf::Mouse::getPosition(window);
					//cout << position.x << "," << position.y << endl;
					if (position.x > 350 && position.x < 550 && position.y>525 && position.y < 575)	//mouse is on Menu button.
					{
						this->mode = 0;
						this->mainmenu.Display(this->window);

					}
					else if (position.x > 50 && position.x < 250 && position.y>525 && position.y < 575)	//mouse is on Undo button.
					{
						this->board.Undo();
						this->board.Display(this->window);
					}
					else
					{
						this->board.put(this->window);
					}

				}
			}
		}
	}
}