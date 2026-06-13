#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include <ncurses.h>

#include "constants.h"
#include "colors.h"
#include "gameloop.h"
#include "getdiff.h"
#include "retry.h"



int main(int argc, char** argv) {
	if (argc > 1) {
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0) {
			printf("The Phi Project - snake\nVersion: %s\n", VERSION);
			return EXIT_SUCCESS;
		}
	}

	initscr();
	raw(); // every character is simply passed to program rather than waiting for terminal driver
	noecho(); // dont echo the typed characters while doing `getch()`
	keypad(stdscr, TRUE); // allow arrow key usage

	if (!has_colors()) {
		endwin();
		printf("The game `snake` requires colors\n");
		return EXIT_FAILURE;
	}
	start_color(); // allow color mode
	initColors(); // creates the custom colors for the game
	
	int maxy, maxx;
	getmaxyx(stdscr, maxy, maxx);
	if (maxy < FULL_ROWS || maxx < FULL_COLS) {
		endwin();
		printf("The game `snake` requires a minimum size of %ix%i\n", FULL_COLS, FULL_ROWS);
		return EXIT_FAILURE;
	}

	curs_set(0); // make the cursor invisible
	wbkgd(stdscr, ' ' | COLOR_PAIR(BLACK)); // set a black background

	srand(time(NULL));

	int difficulty = getdiff(maxy, maxx);

	gameloop(maxy, maxx, difficulty);

	erase();

	int next = retry(maxy, maxx);
	while (next != 0) {
		erase();
		
		if (next == 2) {
			difficulty = getdiff(maxy, maxx);
		}

    gameloop(maxy, maxx, difficulty);

		erase();

		next = retry(maxy, maxx);
  }

	reset_shell_mode(); // resets colors for regular terminal use
	endwin();

  return EXIT_SUCCESS;
}
