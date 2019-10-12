#include <ncurses.h>
#include "RootComponent.h"
#include "utils.h"
using namespace cupasy;

#define DEBUG(x) //x
#ifdef DEBUG
#include <unistd.h>
#endif

RootComponent::RootComponent() : Component(0, 0) {
	// init ncurses
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	raw();
	keypad(stdscr, true);
	curs_set(0);

	// init root component
	ulong width;
	ulong height;
	getmaxyx(stdscr, height, width);
	resize(width, height);
}

bool RootComponent::draw() const {
	cchar_t tmp;

	for(size_t x=0; x<getWidth(); ++x) {
		for(size_t y=0; y<getHeight(); ++y) {
			tmp = INVALID_CCHAR;
			if(getCharAt(x, y, tmp)) {
				DEBUG({
					mvaddch(y, x, '#');
					refresh();
					usleep(20e3);
				})
				mvadd_wch(y, x, &tmp);
			}
		}
	}

	return true;
}

bool RootComponent::draw(ulong minX, ulong minY, ulong maxX, ulong maxY, const Component* child) const {
	resolveChildPosition(minX, minY, maxX, maxY, child);

	cchar_t tmp;

	for(ulong x=minX; x<=maxX; ++x) {
		for(ulong y=minY; y<=maxY; ++y) {
			tmp = INVALID_CCHAR;
			if(getCharAt(x, y, tmp)) {
				DEBUG({
					mvaddch(y, x, '#');
					refresh();
					usleep(1e3);
				})
				mvadd_wch(y, x, &tmp);
			}
			else {
				mvaddch(y, x, ' ');
			}
		}
	}

	return true;
}
