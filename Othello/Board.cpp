#include "Board.h"
#include <iostream>
#include <Windows.h>


Board::Board():undo("Undo",50,525),menu("Menu",350,525),p(1),AI(true),getCorner(false)		//prepare button
{
	for (int i = 0; i < 8; i++)
	{
		this->Coordinate.push_back(vector<int>());
		for (int j = 0; j < 8; j++)
		{
			this->Coordinate[i].push_back(0);
			pieces[i][j] = new Piece(0, i, j);
		}
	}
}

void Board::init(bool AI)
{
	this->getCorner = false;
	this->AI = AI;
	p = 1;
	this->pUndoList = std::stack<int>();
	this->undoList = std::stack<vector<vector<int>>>();
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->Coordinate[i][j] = 0;
		}
	}
	this->Coordinate[3][3] = 2;
	this->Coordinate[3][4] = 1;
	this->Coordinate[4][3] = 1;
	this->Coordinate[4][4] = 2;
}

void Board::Display(sf::RenderWindow& window)				//draw button and board
{
	window.clear();
	sf::RectangleShape Rec(sf::Vector2f(500.f,500.f));
	Rec.setPosition(50.f, 15.f);
	window.draw(Rec);

	//Draw valid cells.
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (OK(i, j) == true)
			{
				sf::RectangleShape valid(sf::Vector2f(65, 65));
				valid.setPosition(50 + 62.5*j-1, 15 + 62.5*i-1);
				valid.setFillColor(sf::Color::Green);
				window.draw(valid);
			}
		}
	}
	Rec.setSize(sf::Vector2f(60.f, 60.f));
	Rec.setFillColor(sf::Color::Black);
	float x = 51.25;
	float y = 16.25;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Rec.setPosition(x, y);
			window.draw(Rec);
			x += 62.5;
		}
		x = 51.25;
		y += 62.5;
	}
	undo.draw(window);
	menu.draw(window);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->pieces[i][j]->change_status(this->Coordinate[i][j]);
			pieces[i][j]->draw(window);
		}
	}

	Piece ex;
	ex.setPosition(sf::Vector2f(600, 50));
	ex.change_status(this->p);
	ex.draw(window);

	sf::Text text;
	sf::Font font;

	if (!font.loadFromFile("arial.ttf"))
	{
		std::cout << "Error";
	}
	text.setFont(font);
	text.setString("Turn");
	text.setCharacterSize(30);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	text.setPosition(670, 60);
	window.draw(text);

	this->blacknum = this->num(1);
	this->whitenum = this->num(2);

	Piece black;
	black.setPosition(sf::Vector2f(600, 200));
	black.change_status(1);
	black.draw(window);


	text.setString(": "+std::to_string(this->blacknum));
	text.setPosition(670, 210);
	window.draw(text);

	Piece white;
	white.setPosition(sf::Vector2f(600, 400));
	white.change_status(2);
	white.draw(window);


	text.setString(": " + std::to_string(this->whitenum));
	text.setPosition(670, 410);
	window.draw(text);

	if (this->end_())
	{
		text.setPosition(sf::Vector2f(600, 300));
		if (this->blacknum > this->whitenum)
		{
			if (this->AI)
				text.setString("You Win!");
			else
				text.setString("Black Win!");
			window.draw(text);
		}
		else if (this->blacknum <this->whitenum)
		{
			if (this->AI)
			{
				text.setCharacterSize(24);
				text.setString("Computer Win!");
			}
			else 
				text.setString("White Win!");
			window.draw(text);
		}
		else
		{
			text.setString("Draw!");
			window.draw(text);
		}
	}



	window.display();

}


bool Board::playOK(int r, int c, int dr, int dc) //To judge which direction of which grid we can put pieces.
{
	if (this->Coordinate[r][c] != 0)
	{
		return false;
	}
	int tr = r, tc = c;
	//tr and tc epresents the coordinates after the point moves in a particular direction through rows and columns.
	while (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && this->Coordinate[tr + dr][tc + dc] == 3 - p)
	{
		//Loop traversal. If the pieces that did not reach the boundary 
		//or the right piece is the other side of the loop then continue, or loop out.
		tr += dr, tc += dc;    //Move the coordinates.
	}
	if (tr == r && tc == c)return false;
	if (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && this->Coordinate[tr + dr][tc + dc] == p)
	{
		return true;
	}
	return false;
}

bool Board::OK(int r, int c) //To judge which grid we can put piece
{
	if (this->Coordinate[r][c] != 0)
	{
		return false;
	}
	for (int i = 0; i < 8; i++)  //As long as one direction satisfy the conditions, it can go.
	{
		if (playOK(r, c, dr[i], dc[i]))
		{
			return true;
		}
	}
	return false;
}


void Board::turn(int tr, int tc, int dr, int dc)  
{
	if (!playOK(tr, tc, dr, dc))
		return;
	while (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && this->Coordinate[tr + dr][tc + dc] == 3 - p)
	{
		this->Coordinate[tr + dr][tc + dc] = p; //Change the color of pieces.
		tr += dr, tc += dc;
	}
}

void Board::put(sf::RenderWindow& window)
{
	sf::Vector2i position;
	bool end = false;
	position = sf::Mouse::getPosition(window);
	if (position.x > 50 && position.x < 550 && position.y>15 && position.y < 515)	//mouse is on board
	{
		int row = (position.y - 15) / 62.5;
		int col = (position.x - 50) / 62.5;
		std::cout << row << "," << col << endl;
		if (OK(row, col))
		{
			undoList.push(this->Coordinate);
			pUndoList.push(this->p);
			for (int i = 0; i < 8; i++)
			{
				turn(row, col, dr[i], dc[i]);
			}
			this->Coordinate[row][col] = p;
			p = 3 - p;
			if (this->end_())
			{
				end = true;
			}
			this->Display(window);
			if (end)
				return;
			if (p==2&&this->AI)
			{
				while (p == 2)
				{
					AIPlay(row, col);
					if (OK(row, col))
					{
						for (int i = 0; i < 8; i++)
						{
							turn(row, col, dr[i], dc[i]);
						}
						this->Coordinate[row][col] = p;
						p = 3 - p;
						if (this->end_())
							end = true;
						Sleep(1000);
						this->Display(window);
						if (end)
							return;
					}
				}
			}
		}
	}
}

bool Board::end_()  //To judge if the game over or not.
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (OK(i, j)) {
				return false;
			}
		}
	}
	p = 3 - p;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (OK(i, j))
			{
				return false;
			}
		}
	}

	cout << "\ngame over\n";
	if (num(1) < num(2))
	{
		cout << "white win";
	}
	else if (num(1) > num(2))
	{
		cout << "black win";
	}
	else
	{
		cout << "A draw";
	}
	return true;
}

int Board::num(int k)  //Count the number of pieces: 1-black, 2-white.
{
	int s = 0;
	for (int i = 0; i < 8; i++)for (int j = 0; j < 8; j++)
	{
		if (this->Coordinate[i][j] == k)
		{
			s++;
		}
	}
	return s;
}

void Board::Undo()
{
	if (!undoList.empty())
	{
		this->Coordinate = undoList.top();
		undoList.pop();
		this->p = pUndoList.top();
		pUndoList.pop();
	}
}


void Board::AIPlay(int& row, int& col)
{
	if ((OK(0, 0)) || (OK(0, 7)) || (OK(7, 0)) || (OK(7, 7)) && getCorner == false)
	{
		int max = 0;
		if (OK(0, 0) && occupyNum(0, 0) > max)
		{
			max = occupyNum(0, 0);
			row = 0;
			col = 0;
		}
		if (OK(0, 7) && occupyNum(0, 7) > max)
		{
			max = occupyNum(0, 7);
			row = 0;
			col = 7;
		}
		if (OK(7, 0) && occupyNum(7, 0) > max)
		{
			max = occupyNum(7, 0);
			row = 7;
			col = 0;
		}
		if (OK(7, 7) && occupyNum(7, 7) > max)
		{
			max = occupyNum(7, 7);
			row = 7;
			col = 7;
		}
		this->getCorner = true;
		return;
	}

	int max = 0;
	bool flag = false;
	if (OK(2, 0) && occupyNum(2, 0) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(2, 0);
		row = 2;
		col = 0;
	}
	if (OK(5, 0) && occupyNum(5, 0) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(5, 0);
		row = 5;
		col = 0;
	}
	if (OK(2, 7) && occupyNum(2, 7) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(2, 0);
		row = 2;
		col = 7;
	}
	if (OK(5, 7) && occupyNum(5, 7) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(5, 0);
		row = 5;
		col = 7;
	}
	if (OK(0, 2) && occupyNum(0, 2) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(0, 2);
		row = 0;
		col = 2;
	}
	if (OK(0, 5) && occupyNum(0, 5) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(0, 5);
		row = 0;
		col = 5;
	}
	if (OK(7, 2) && occupyNum(7, 2) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(7, 2);
		row = 7;
		col = 2;
	}
	if (OK(7, 5) && occupyNum(7, 5) > max&&getCorner == false)
	{
		flag = true;
		max = occupyNum(7, 5);
		row = 7;
		col = 5;
	}
	if (flag)
	{
		return;
	}
	max = 0;
	flag = false;
	for (int i = 2; i <= 5; i++)
	{
		if (OK(i, 0) && occupyNum(i, 0) > max&&getCorner == false)
		{
			flag = true;
			max = occupyNum(i, 0);
			row = i;
			col = 0;
		}
	}
	for (int i = 2; i <= 5; i++)
	{
		if (OK(i, 7) && occupyNum(i, 7) > max&&getCorner == false)
		{
			flag = true;
			max = occupyNum(i, 7);
			row = i;
			col = 7;
		}
	}
	for (int j = 2; j <= 5; j++)
	{
		if (OK(0, j) && occupyNum(0, j) > max&&getCorner == false)
		{
			flag = true;
			max = occupyNum(0, j);
			row = 0;
			col = j;
		}
	}
	for (int j = 2; j <= 5; j++)
	{
		if (OK(7, j) && occupyNum(7, j) > max&&getCorner == false)
		{
			flag = true;
			max = occupyNum(7, j);
			row = 7;
			col = j;
		}
	}
	if (flag)
	{
		return;
	}

	int min = 64;
	flag = false;

	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (!(i <= 1 ||  j >= 6|| i >= 6 || j <= 1) && getCorner == false)
			{
				if (OK(i, j) == true)
				{
					if (enemyAvalNum(i, j) < min)
					{
						flag = true;
						min = enemyAvalNum(i, j);
						row = i;
						col = j;
					}
				}
			}
		}
	}

	if (flag)
	{
		return;
	}

	min = 64;
	flag = false;

	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (!((i <= 1 && j <= 1) || (i <= 1 && j >= 6) || (i >= 6 && j <= 1) || (i >= 6 && j >= 6)) && getCorner == false)
			{
				if (OK(i, j) == true)
				{
					if (enemyAvalNum(i, j) < min)
					{
						flag = true;
						min = enemyAvalNum(i, j);
						row = i;
						col = j;
					}
				}
			}
		}
	}


	if (flag)
		return;

	max = 0;
	flag = false;

	
	for (int i = 0; i <= 7; i++)						//Around the corners.
	{
		for (int j = 0; j <= 7; j++)
		{
			if (OK(i, j)&&((i!=1||j!=1) && (i != 1 || j != 6) &&(i != 6 || j != 1) && (i != 6 || j != 6)) && getCorner == false)
			{
				undoList.push(this->Coordinate);
				pUndoList.push(this->p);
				for (int k = 0; k < 8; k++)
				{
					turn(i, j, dr[k], dc[k]);
				}
				this->Coordinate[i][j] = p;
				p = 3 - p;
				if (OK(0, 0)||OK(0,7)||OK(7,0)||OK(7,7))												//Make sure player cannot get corner.
				{
					this->Undo();
					continue;
				}
				else
				{
					int result = 0;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (OK(i, j) == true)
							{
								result += 1;
							}
						}
					}
					if (result > max)
					{
						flag = true;
						max = result;
						row = i;
						col = j;
					}
				}
				this->Undo();
			}
		}
	}
	if (flag)
		return;
	for (int i = 0; i <= 7; i++)						//Around the corners.
	{
		for (int j = 0; j <= 7; j++)
		{
			if (OK(i, j)&&getCorner==false)
			{
				undoList.push(this->Coordinate);
				pUndoList.push(this->p);
				for (int k = 0; k < 8; k++)
				{
					turn(i, j, dr[k], dc[k]);
				}
				this->Coordinate[i][j] = p;
				p = 3 - p;
				if (OK(0, 0) || OK(0, 7) || OK(7, 0) || OK(7, 7))												//Make sure player cannot get corner.
				{
					this->Undo();
					continue;
				}
				else
				{
					int result = 0;
					for (int i = 0; i < 8; i++)
					{
						for (int j = 0; j < 8; j++)
						{
							if (OK(i, j) == true)
							{
								result += 1;
							}
						}
					}
					if (result > max)
					{
						flag = true;
						max = result;
						row = i;
						col = j;
					}
				}
				this->Undo();
			}
		}
	}
	if (flag)
		return;
	for (int i = 0; i <= 7; i++)
	{
		for (int j = 0; j <= 7; j++)
		{
			if (OK(i, j) == true)
			{
				if (OK(i, j) && occupyNum(i, j) > max)
				{
					max = occupyNum(i, j);
					row = i;
					col = j;
				}
			}
		}
	}

}



int Board::occupyNum(int row, int col)
{
	int before = this->whitenum;
	undoList.push(this->Coordinate);
	pUndoList.push(this->p);
	for (int k = 0; k < 8; k++)
	{
		turn(row, col, dr[k], dc[k]);
	}
	this->Coordinate[row][col] = p;
	p = 3 - p;
	this->end_();
	int result = this->num(2)-before;
	this->Undo();
	return result;
}

int Board::enemyAvalNum(int row, int col)
{
	undoList.push(this->Coordinate);
	pUndoList.push(this->p);
	for (int k = 0; k < 8; k++)
	{
		turn(row, col, dr[k], dc[k]);
	}
	this->Coordinate[row][col] = p;
	p = 3 - p;
	this->end_();
	int result = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (OK(i, j) == true)
			{	
				result += 1;
			}
		}
	}
	this->Undo();
	return result;
}