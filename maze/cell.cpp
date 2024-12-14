#include "cell.h"
#include <ncurses.h>

int rows = DEFAULT_ROWS;  
int columns = DEFAULT_COLUMNS; 
int bombs = DEFAULT_BOMBS;
int x_offset = 0;
int y_offset = 1; 
int x_win;
int y_win;

Cell::Cell()
{
	randomFieldGenerate();
	fixSinglePassage();
	addBombPassage(bombs, 0);
}

Cell::~Cell()
{

}

void Cell::reset()
{
	randomFieldGenerate();
	fixSinglePassage();
	addBombPassage(bombs, 0);
}

void Cell::printField()
{
	for(int i = 0; i < rows; i++)
	{
		for(int j = 0; j < columns; j++)
		{
			switch (cell_table[i][j])
			{
			case Content::BOMB:
				mvwaddch(stdscr, i + y_offset + 1, j + x_offset + 1, 'B');
				break;
			case Content::PASSAGE:
				mvwaddch(stdscr, i + y_offset + 1, j + x_offset + 1, ' ');
				break;
			case Content::WALL:
				mvwaddch(stdscr, i + y_offset + 1, j + x_offset + 1, ACS_CKBOARD);
				break;
			default:
				break;
			}
		}
	}
}

void Cell::printWalls()
{
	
	for(int i = 0; i < (rows + 2); i++)
	{
		for(int j = 0; j < (columns + 2); j++)
		{
			if((i == 0) || (i == (rows + 1)) || (j == 0) || (j == (columns + 1)))
			{
				mvwaddch(stdscr, i + y_offset, j + x_offset, ACS_CKBOARD);
			}
		}
	}

	// This line is added for the last passage inside outer wall 
	mvwaddch(stdscr, rows + y_offset, columns + 1 + x_offset, ' ');
}

bool Cell::isWall(int x, int y)
{
	if((y == y_offset) || (x == x_offset))
		return true;
	else if(cell_table[y - y_offset - 1][x - x_offset - 1] == Content::WALL)
		return true;
	else
		return false;
}

bool Cell::isBomb(int x, int y)
{
	if(cell_table[y - y_offset - 1][x - x_offset - 1] == Content::BOMB)
		return true;
	else
		return false;
}