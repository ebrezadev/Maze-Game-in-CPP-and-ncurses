#include "cell.h"
#include <iostream>
#include <ncurses.h>

void Cell::randomFieldGenerate()
{
	// iterate over the cells and fill them with WALLs and PASSAGEs
	// like a checkerboard, with PASSAGEs in even numbered cells
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (((i % 2) == 0) && ((j % 2) == 0))
				cell_table[i][j] = Content::PASSAGE;
			else
				cell_table[i][j] = Content::WALL;
			// fill the visited table with default values
			visit_table[i][j].visited = false;
			visit_table[i][j].previous_cell = {j, i};
		}
	}

	int i, j, next_i, next_j, mid_i, mid_j;

	// Randomly select an i,j for the initial cell
	// it must be a PASSAGE cell surrounded by WALLs
	// if not a PASSAGE cell, select again.

	std::srand(time(0));

	if (true)
	{
		for (;;)
		{
			i = std::rand() % rows;

			j = std::rand() % columns;

			if (cell_table[i][j] != Content::PASSAGE)
				continue;
			else
				break;
		}
	}

	// mark this initial cell as visited
	visit_table[i][j].visited = true;

	for (;;)
	{
		bool case_0 = false;
		bool case_1 = false;
		bool case_2 = false;
		bool case_3 = false;

		for (;;)
		{
			// Randomly select a neighbor cell out of maximum 4 neighbors (0,1,2,3)
			// Repeat if the selected cell is out of range

			int random_number = std::rand() % 4;

			if (((random_number == 0) && case_0) || ((random_number == 1) && case_1) || ((random_number == 2) && case_2) || ((random_number == 3) && case_3))
				continue;

			switch (random_number)
			{
			case 0:
				next_i = i - 2;
				next_j = j;
				mid_i = i - 1;
				mid_j = j;
				case_0 = true;
				break;
			case 1:
				next_i = i;
				next_j = j + 2;
				mid_i = i;
				mid_j = j + 1;
				case_1 = true;
				break;
			case 2:
				next_i = i + 2;
				next_j = j;
				mid_i = i + 1;
				mid_j = j;
				case_2 = true;
				break;
			case 3:
				next_i = i;
				next_j = j - 2;
				mid_i = i;
				mid_j = j - 1;
				case_3 = true;
				break;
			default:
				break;
			}

			// Check if the neighbor cell doesnt fall inside boundaries
			if ((next_i < 0) || (next_i >= rows) || (next_j < 0) || (next_j >= columns))
			{
				// Check if all the neighbor cells are already tried out
				if (case_0 && case_1 && case_2 && case_3)
				{
					// check if the previous cell in visit table is the same cell. This indicates the finishing condition
					if ((visit_table[i][j].previous_cell.y == i) && (visit_table[i][j].previous_cell.x == j))
					{
						return;
					}
					else // If a previous cell exists, turn back to previous cell and start over again checking all 4 neighbors
					{
						i = visit_table[i][j].previous_cell.y;
						j = visit_table[i][j].previous_cell.x;
						case_0 = case_1 = case_2 = case_3 = false;

						continue;
					}
				}

				continue;
			}
			else if (visit_table[next_i][next_j].visited == true) // If the nighboring cell falls inside boundaries, check if it has been already visited
			{
				if (case_0 && case_1 && case_2 && case_3)
				{
					if ((visit_table[i][j].previous_cell.y == i) && (visit_table[i][j].previous_cell.x == j))
					{
						return;
					}
					else
					{
						i = visit_table[i][j].previous_cell.y;
						j = visit_table[i][j].previous_cell.x;
						case_0 = case_1 = case_2 = case_3 = false;

						continue;
					}
				}

				continue;
			}
			else  // If the neighbor cell falls inside boundaries and has not been visited, break and jump into it
				break;
		}
		
		// Change the inner wall between neighbors into a passage
		// Mark both the neighbor cell and the inner passage as visited
		visit_table[next_i][next_j].visited = true;
		visit_table[next_i][next_j].previous_cell.x = j;
		visit_table[next_i][next_j].previous_cell.y = i;
		cell_table[next_i][next_j] = Content::PASSAGE;

		visit_table[mid_i][mid_j].visited = true;
		visit_table[mid_i][mid_j].previous_cell.x = j;
		visit_table[mid_i][mid_j].previous_cell.y = i;
		cell_table[mid_i][mid_j] = Content::PASSAGE;

		i = next_i;
		j = next_j;
	}
}

void Cell::fixSinglePassage()
{
	int i, j, next_i, next_j, mid_i, mid_j;

	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
		{
			// Check if a passage cell has not been visited yet, which indicates a single isolated passage
			if ((cell_table[i][j] == Content::PASSAGE) && (visit_table[i][j].visited == false))
			{
				bool case_0 = false;
				bool case_1 = false;
				bool case_2 = false;
				bool case_3 = false;

				// Randomly find a neighbor cell for the isolated passage to connect them together
				for (;;)
				{
					int random_number = std::rand() % 4;

					if (((random_number == 0) && case_0) || ((random_number == 1) && case_1) || ((random_number == 2) && case_2) || ((random_number == 3) && case_3))
						continue;

					switch (random_number)
					{
					case 0:
						next_i = i - 2;
						next_j = j;
						mid_i = i - 1;
						mid_j = j;
						case_0 = true;
						break;
					case 1:
						next_i = i;
						next_j = j + 2;
						mid_i = i;
						mid_j = j + 1;
						case_1 = true;
						break;
					case 2:
						next_i = i + 2;
						next_j = j;
						mid_i = i + 1;
						mid_j = j;
						case_2 = true;
						break;
					case 3:
						next_i = i;
						next_j = j - 2;
						mid_i = i;
						mid_j = j - 1;
						case_3 = true;
						break;
					default:
						break;
					}

					if ((next_i < 0) || (next_i >= rows) || (next_j < 0) || (next_j >= columns))
					{
						continue;
					}

					break;
				}

				visit_table[i][j].visited = true;
				visit_table[mid_i][mid_j].visited = true;
				cell_table[mid_i][mid_j] = Content::PASSAGE;
			}
		}
	}
}

void Cell::addBombPassage(int bombsPercent, int passagesPercent)
{
	int i, j;
	int wallCount = 0;
	int passageCount = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (cell_table[i][j] == Content::WALL)
			{
				wallCount++;
			}
		}
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			if (cell_table[i][j] == Content::PASSAGE)
			{
				passageCount++;
			}
		}
	}

	for (int counter = 0; counter < ((bombsPercent * wallCount) / 100); counter++)
	{
		for (;;)
		{
			i = std::rand() % rows;
			j = std::rand() % columns;
			if (cell_table[i][j] == Content::WALL)
				break;
		}

		cell_table[i][j] = Content::BOMB;
	}

	for (int counter = 0; counter < ((passagesPercent * passageCount) / 100); counter++)
	{
		for (;;)
		{
			i = std::rand() % rows;
			j = std::rand() % columns;
			if (cell_table[i][j] == Content::WALL)
				break;
		}

		cell_table[i][j] = Content::PASSAGE;
	}
}