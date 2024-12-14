#include "states.h"
#include <ncurses.h>
#include <cstring>
#include "fps.h"

const int safe_min_rows = 9;
const int safe_min_columns = 9;
const int min_FPS = 1;
const int max_FPS = 200;
const int min_bombs = 0;
const int max_bombs = 100;

State_Settings::State_Settings()
{
	screen_update_flag = true;
	current_menu = menu_t::BACK;
}

State::state_return_t State_Settings::stateFunction(int input)
{
	int safe_max_rows;
	int safe_max_columns;

	static int set_rows = DEFAULT_ROWS;
	static int set_columns = DEFAULT_COLUMNS;
	static int set_bombs = DEFAULT_BOMBS;
	static int set_FPS = DEFAULT_FPS;

	getmaxyx(stdscr, max_rows, max_columns);

	if (max_rows % 2 == 0)
		safe_max_rows = max_rows - 5;
	else
		safe_max_rows = max_rows - 6;

	if (max_columns % 2 == 0)
		safe_max_columns = max_columns - 5;
	else
		safe_max_columns = max_columns - 6;

	State_list_t next_state = State_list_t::State_Settings;

	if (screen_update_flag)
	{
		getmaxyx(stdscr, max_rows, max_columns);
		erase();
		attron(A_BOLD);
		mvprintw(3, (max_columns - strlen("SETTINGS")) / 2, "%s", "SETTINGS");
		attroff(A_BOLD);

		if (current_menu == menu_t::ROWS_SETTING)
		{
			mvwaddch(stdscr, 5, ((max_columns - strlen("rows: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			attron(A_DIM);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("bombs: ") - 4) / 2, "bombs: %d%%", set_bombs);
			mvprintw(8, (max_columns - strlen("FPS: ") - 3) / 2, "FPS: %d", set_FPS);
			mvprintw(9, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			mvwaddch(stdscr, 6, ((max_columns - strlen("columns: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(7, (max_columns - strlen("bombs: ") - 4) / 2, "bombs: %d%%", set_bombs);
			mvprintw(8, (max_columns - strlen("FPS: ") - 3) / 2, "FPS: %d", set_FPS);
			mvprintw(9, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::BOMBS_SETTING)
		{
			mvwaddch(stdscr, 7, ((max_columns - strlen("bombs: ") - 4) / 2) - 2, ACS_DIAMOND);
			mvprintw(7, (max_columns - strlen("bombs: ") - 4) / 2, "bombs: %d%%", set_bombs);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(8, (max_columns - strlen("FPS: ") - 3) / 2, "FPS: %d", set_FPS);
			mvprintw(9, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::FPS_SETTING)
		{
			mvwaddch(stdscr, 8, ((max_columns - strlen("FPS: ") - 3) / 2) - 2, ACS_DIAMOND);
			mvprintw(8, (max_columns - strlen("FPS: ") - 3) / 2, "FPS: %d", set_FPS);
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("bombs: ") - 4) / 2, "bombs: %d%%", set_bombs);
			mvprintw(9, (max_columns - strlen("back")) / 2, "%s", "back");
			attroff(A_DIM);
		}
		else if (current_menu == menu_t::BACK)
		{
			mvwaddch(stdscr, 9, ((max_columns - strlen("exit")) / 2) - 2, ACS_DIAMOND);
			mvprintw(9, (max_columns - strlen("back")) / 2, "%s", "back");
			attron(A_DIM);
			mvprintw(5, (max_columns - strlen("rows: ") - 3) / 2, "rows: %d", set_rows);
			mvprintw(6, (max_columns - strlen("columns: ") - 3) / 2, "columns: %d", set_columns);
			mvprintw(7, (max_columns - strlen("bombs: ") - 4) / 2, "bombs: %d%%", set_bombs);
			mvprintw(8, (max_columns - strlen("FPS: ") - 3) / 2, "FPS: %d", set_FPS);
			attroff(A_DIM);
		}

		attron(A_ITALIC | A_DIM);
		mvprintw(12, (max_columns - strlen("UP/DOWN to choose")) / 2, "UP/DOWN to choose");
		mvprintw(13, (max_columns - strlen("LEFT/RIGHT to change")) / 2, "LEFT/RIGHT to change");
		mvprintw(14, (max_columns - strlen("SPACE to set defaults")) / 2, "SPACE to set defaults");
		attroff(A_ITALIC | A_DIM);
	}

	switch (input)
	{
	case KEY_UP:
		current_menu = (menu_t)(((int)current_menu + 4) % 5);
		screen_update_flag = true;
		break;
	case KEY_DOWN:
		current_menu = (menu_t)(((int)current_menu + 1) % 5);
		screen_update_flag = true;
		break;
	case (int)13:
		if (current_menu == menu_t::BACK)
		{
			rows = set_rows;
			columns = set_columns;
			FPS = set_FPS;
			period_ms = 1000 / FPS;
			input_timeout_ms = period_ms / 2;
			sleep_ms = period_ms / 4;
			bombs = set_bombs;
			next_state = State_list_t::State_Main_Menu;
			screen_update_flag = true;
		}
		else
			screen_update_flag = false;
		break;
	case KEY_LEFT:
		if (current_menu == menu_t::ROWS_SETTING)
		{
			if (set_rows > safe_min_rows)
				set_rows -= 2;
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			if (set_columns > safe_min_columns)
				set_columns -= 2;
		}
		else if (current_menu == menu_t::BOMBS_SETTING)
		{
			if (set_bombs > min_bombs)
				set_bombs--;
		}
		else if (current_menu == menu_t::FPS_SETTING)
		{
			if (set_FPS > min_FPS)
				set_FPS--;
		}
		screen_update_flag = true;
		break;
	case KEY_RIGHT:
		if (current_menu == menu_t::ROWS_SETTING)
		{
			if ((set_rows < safe_max_rows) && (set_rows < (MAX_ROWS - 2)))
				set_rows += 2;
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			if ((set_columns < safe_max_columns) && (set_columns < (MAX_COLS - 2)))
				set_columns += 2;
		}
		else if (current_menu == menu_t::BOMBS_SETTING)
		{
			if (set_bombs < max_bombs)
				set_bombs++;
		}
		else if (current_menu == menu_t::FPS_SETTING)
		{
			if (set_FPS < max_FPS)
				set_FPS++;
		}
		screen_update_flag = true;
		break;
	case ' ':
		if (current_menu == menu_t::ROWS_SETTING)
		{
			set_rows = DEFAULT_ROWS;
		}
		else if (current_menu == menu_t::COLUMNS_SETTING)
		{
			set_columns = DEFAULT_COLUMNS;
		}
		else if (current_menu == menu_t::BOMBS_SETTING)
		{
			set_bombs = DEFAULT_BOMBS;
		}
		else if (current_menu == menu_t::FPS_SETTING)
		{
			set_FPS = DEFAULT_FPS;
		}
		screen_update_flag = true;
		break;
	default:
		screen_update_flag = false;
		break;
	}

	if (set_rows > safe_max_rows)
	{
		set_rows = safe_max_rows;
		screen_update_flag = true;
	}
	if (set_columns > safe_max_columns)
	{
		set_columns = safe_max_columns;
		screen_update_flag = true;
	}

	return {next_state, screen_update_flag};
}