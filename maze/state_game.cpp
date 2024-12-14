#include "states.h"
#include <ncurses.h>
#include <cstring>
#include <alphabet_draw.h>

State_Game::State_Game()
{
	screen_update_flag = true;
} 

State_Game::state_return_t State_Game::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Game;

	getmaxyx(stdscr, max_rows, max_columns);

	if(screen_update_flag)
	{
		maze.print();
	}

	switch (input)
	{
	case KEY_UP:
		maze.movePlayer(0, -1);
		screen_update_flag = true;
		break;
	case KEY_DOWN:
		maze.movePlayer(0, 1);
		screen_update_flag = true;
		break;
	case KEY_RIGHT:
		maze.movePlayer(1, 0);
		screen_update_flag = true;
		break;
	case KEY_LEFT:
		maze.movePlayer(-1, 0);
		screen_update_flag = true;
		break;
	case (int)13:
		screen_update_flag = false;
		break;
	case ' ':
		next_state = State_list_t::State_Pause_Menu;
		screen_update_flag = true;
		break;
	default:
		screen_update_flag = false;
		break;
	}

	if (maze.bombCheck())
	{
		Finished.has_won = false;
		next_state = State_list_t::State_Finished;
	}
	else if (maze.winCheck())
	{
		Finished.has_won = true;
		next_state = State_list_t::State_Finished;
	}

	return {next_state, screen_update_flag};
}

void State_Game::reset()
{
	maze.newField();
	
	screen_update_flag = true;
}

void State_Game::resetPlayer()
{
	maze.resetPlayer();
}
