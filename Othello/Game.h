#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "OnlineMenu.h"
#include "Board.h"

class Game
{
private:
	sf::RenderWindow window;
	MainMenu mainmenu;
	OnlineMenu onlinemenu;
	Board board;
	int mode;					//mode 0: Main Menu.  mode 1: Online Menu.   mode 2: Board

public:
	Game();
	void Play();

};
