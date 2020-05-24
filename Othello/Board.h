#pragma once
#include "Button.h"
#include "Piece.h"
#include <vector>
#include <stack>

class Board
{
private:
	Button undo;
	Button menu;
	vector<vector<int>> Coordinate;
	Piece* pieces[8][8];
	std::stack<vector<int>> stack;
	const int dr[8] = { 0, 0, 1, 1, 1, -1, -1, -1 }, dc[8] = { 1, -1, 0, 1, -1, 0, 1, -1 }; //Eight direction's vector.
	int p;					//Who is this turn: black is 1, white is 2.
	int blacknum;
	int whitenum;
	std::stack<vector<vector<int>>> undoList;
	std::stack<int> pUndoList;
	bool AI;
	int lastPlace[2];
	bool getCorner;
public:
	Board();
	void init(bool AI);
	void Display(sf::RenderWindow& window);		//Use dynamic memory to build piece
	void put(sf::RenderWindow& window);				//Check the mouse place, see if it is valid, put piece and do the logic of Othello.
	bool playOK(int r, int c, int dr, int dc);
	bool OK(int r, int c);
	void turn(int tr, int tc, int dr, int dc);
	bool end_();  //To judge if the game over or not.
	int num(int k);  //Count the number of pieces: 1-black, 2-white.
	void Undo();
	void AIPlay(int& row, int& col);
	int occupyNum(int row, int col);
	int enemyAvalNum(int row, int col);
};
