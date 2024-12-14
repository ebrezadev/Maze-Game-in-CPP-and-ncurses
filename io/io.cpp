#include <ncurses.h>
#include "io.h"

IO *IO::getInstance()
{
	static IO Instance;

	return &Instance;
}

IO::IO()
{
	/* Start curses mode and data structures for stdscr*/
	initscr();
	/* Line buffering disabled, Pass on everything to me; except for 'ctrl + c'*/
	cbreak();
	/* Line buffering disabled, Pass on everything to me; even 'ctrl + c'*/
	//raw();
	nonl();
	// gives the flexibility of echoing characters at any place in the window without updating current (y,x). turn off with echo()
	noecho();
	// It enables the reading of function keys like F1, F2, arrow keys etc for stdscr
	keypad(stdscr, TRUE);

	curs_set(0);
}

IO::~IO()
{
	endwin();
}

void IO::render()
{
	// refresh() checks the window and updates only the portion which has been changed
	refresh();
}

int IO::input(int to)
{
	wtimeout(stdscr, to);
	int keypress = getch();

	return keypress;
}