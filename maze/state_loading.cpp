#include "states.h"
#include <ncurses.h>
#include <thread>
#include <cstring>

// Globals set by the loading thread and read/initialized by the main thread
bool thread_finished = false;
bool thread_in_progress = false;

State_Loading::State_Loading()
{
	screen_update_flag = true;
	thread_finished = false;
	thread_in_progress = false;
}

void loading_thread()
{
	Game.reset();
	thread_finished = true;
}

State_Loading::state_return_t State_Loading::stateFunction(int input)
{
	State_list_t next_state = State_list_t::State_Loading;

	getmaxyx(stdscr, max_rows, max_columns);

	erase();
	mvprintw(max_rows / 2, (max_columns - strlen((char *)"LOADING...")) / 2, "LOADING...");

	if (thread_finished)
	{
		next_state = State_list_t::State_Game;
		thread_finished = false;
		thread_in_progress = false;
		x_win = x_offset + columns;
		y_win = y_offset + rows;
	}
	else if (!thread_in_progress)
	{
		std::thread thread_1{loading_thread};
		thread_1.detach();
		thread_in_progress = true;
		screen_update_flag = true;
	}
	else
	{
		screen_update_flag = false;
	}

	return {next_state, screen_update_flag};
}
