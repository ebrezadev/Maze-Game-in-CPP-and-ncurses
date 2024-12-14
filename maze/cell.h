/*
This file contains class definition for Cell class. Cell is responsible for everything field related:
randomly generating a matrix for the field and printing the outer walls, printing the inner walls
and printing the bombs.

Also, this file contains various globals related to the field and winning conditions.
*/
#ifndef __CELL_H__
#define __CELL_H__

// Using constexpr instead of #define
inline constexpr int MAX_ROWS = 1000;
inline constexpr int MAX_COLS = 1000;
inline constexpr int MINIMUM_COLS = 22;
inline constexpr int MINIMUM_ROWS = 15;
inline constexpr int DEFAULT_BOMBS = 15;
inline constexpr int DEFAULT_ROWS = 15;
inline constexpr int DEFAULT_COLUMNS = 25;

extern int rows;  
extern int columns; 
extern int bombs;
extern int x_offset;
extern int y_offset; 
extern int x_win;
extern int y_win;



class Cell
{
public:
	Cell();
	~Cell();
	void printWalls();
	void printField();
	bool isWall(int x, int y);
	bool isBomb(int x, int y);
	void reset();

private:
	typedef struct 
	{
		int x;
		int y;
	} coordinates_t;

	enum class Content												// Possible content of every cell inside field
	{
		WALL,
		BOMB,
		PASSAGE
	};

	typedef struct 													// Data structure used for visit table
	{
		bool visited;
		coordinates_t previous_cell;
	} visited_cell_info_t;

	Content cell_table[MAX_ROWS][MAX_COLS];							// A static matrix for the field. Each field uses a portion of this matrix
	visited_cell_info_t visit_table[MAX_ROWS][MAX_COLS];			// 2D Matrix of visited_cell_info data structure helping random generation

	void randomFieldGenerate();										// Method for random creation of the field using DFS
	void fixSinglePassage();										// Method for fixing possible isolated single passages
	void addBombPassage(int bombsPercent, int passagesPercent);		// Method for adding bombs and additional passages in place of inner walls
};

#endif