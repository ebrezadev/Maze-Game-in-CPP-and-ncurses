/*
This file includes the class definition for Maze class, responsible for printing the field (using cell object) and player, 
moving the player inside the field, and checking for collisions and winning condition. 
Cell object is dynamically held inside heap, to reset the randomly generated field anytime.
*/

#ifndef __MAZE_H__
#define __MAZE_H__

#include "cell.h"

class Maze
{
public:
	Maze();
	~Maze();
	void movePlayer(int delta_x, int delta_y);
	bool winCheck();
	bool bombCheck();
	void newField();
	void print();
	void resetPlayer();

private:
	int max_columns;
	int max_rows;
	int x_player;
	int y_player;
	Cell *maze_field;									// Pointer to the dynamically created cell
	void printPlayer();
};

#endif