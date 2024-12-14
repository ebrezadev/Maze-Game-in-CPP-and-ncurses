//###
#include "maze.h"
#include <ncurses.h>
#include <cstring>

Maze::Maze()
{
	x_player = 1 + x_offset;
	y_player = 1 + y_offset;
	
	maze_field = nullptr;
}

Maze::~Maze()
{
	
}

void Maze::movePlayer(int delta_x, int delta_y)
{
	// Check if player is moving inside boundaries
	if(((x_player + delta_x) >= (1 + x_offset)) && ((x_player + delta_x) < (columns + x_offset + 1)) && !maze_field->isWall(x_player + delta_x, y_player + delta_y))
	{
		x_player += delta_x;
	}

	if(((y_player + delta_y) >= (1 + y_offset)) && ((y_player + delta_y) < (rows + y_offset + 1)) && !maze_field->isWall(x_player + delta_x, y_player + delta_y))
	{
		y_player += delta_y;
	}
}

bool Maze::bombCheck()
{
	if(maze_field->isBomb(x_player, y_player))
		return true;
	else
		return false;
}

bool Maze::winCheck()
{
	if((x_player == (x_win)) && (y_player == (y_win)))
		return true;
	else
		return false;
}

void Maze::newField()
{
	x_player = 1 + x_offset;
	y_player = 1 + y_offset;

	if(maze_field != nullptr)
	{
		delete maze_field;
	}

	maze_field = new Cell;
}

void Maze::printPlayer()
{
	mvwaddch(stdscr, y_player, x_player, ACS_DIAMOND);
}

void Maze::print()
{
	getmaxyx(stdscr, max_rows, max_columns);

	erase();

	mvprintw(y_offset - 1, (max_columns - strlen((char *)"hit SPACE for menu")) / 2, (char *)"hit SPACE for menu");

	maze_field->printWalls();

	maze_field->printField();

	printPlayer();
}

void Maze::resetPlayer()
{
	x_player = 1 + x_offset;
	y_player = 1 + y_offset;
}