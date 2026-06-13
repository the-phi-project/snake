#include "getdiff.h"

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "colors.h"
#include "constants.h"

const char* buttons[] = {"EASY", "NORMAL", "HARD"};  // worst. syntax. ever.
const int colors[] = {WHITE_GREEN, WHITE_CYAN, WHITE_GOLD};
const int xpositions[] = {2, 8, 17};


/// Supposedly the best way to do this is to not update
/// button attributes, but redraw the entire window
int getdiff(int maxy, int maxx) {
  refresh();

  WINDOW* win;
  int starty = (maxy - WIN_HEIGHT) / 2;
  int startx = (maxx - WIN_WIDTH) / 2;

  int current = NORMAL; // start with normal

  win = drawGetDiffWin(starty, startx, current);
  wrefresh(win);

  int ch;
  while ((ch = getch()) != 10) { // hardcoded ENTER key, !!!NOT!!! KEY_ENTER
    refresh();
    switch (ch) {
      case KEY_LEFT:
        current = max(0, current - 1);
        break;
      case KEY_RIGHT:
        current = min(2, current + 1);
        break;
      default:
        continue;
    }

    werase(win);
    drawGetDiffWin(starty, startx, current);
  }

  delwin(win);
  return current;
}

WINDOW* drawGetDiffWin(int starty, int startx, int active) {
  refresh();

  WINDOW* win = newwin(WIN_HEIGHT, WIN_WIDTH, starty, startx);

#define C | A_BOLD
  wborder(win, '|' C, '|' C, '-' C, '-' C, '+' C, '+' C, '+' C, '+' C);

  mvwaddstr(win, 1, (WIN_WIDTH - 11) / 2, "DIFFICULTY?");

  /* BUTTONS */
  for (int i = 0; i < 3; i++) {
    if (i == active) {
      wattron(win, COLOR_PAIR(colors[i]));
    }
    
    mvwaddstr(win, 3, xpositions[i], buttons[i]);

    if (i == active) {
      wattroff(win, COLOR_PAIR(colors[i]));
    }
  }

  wrefresh(win);

  return win;
}