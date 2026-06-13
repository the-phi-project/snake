#include "retry.h"

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "colors.h"
#include "constants.h"

#define EXIT 0
#define RESPAWN 1
#define DIFFICULTY 2

const char* retry_buttons[] = {"EXIT", "RESPAWN", "DIFFICULTY"};  // worst. syntax. ever.
const int retry_colors[] = {WHITE_RED, WHITE_GREEN, WHITE_CYAN};
const int retry_xpositions[] = {2, 8, 17};

/// Supposedly the best way to do this is to not update
/// button attributes, but redraw the entire window
int retry(int maxy, int maxx) {
  refresh();

  WINDOW* win;
  int starty = (maxy - RETRY_WIN_HEIGHT) / 2;
  int startx = (maxx - RETRY_WIN_WIDTH) / 2;

  int current = RESPAWN;  // start with respawn

  win = drawRetryWin(starty, startx, current);
  wrefresh(win);

  int ch;
  while ((ch = getch()) != 10) {  // hardcoded ENTER key, !!!NOT!!! KEY_ENTER
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
    drawRetryWin(starty, startx, current);
  }

  delwin(win);
  return current;
}

WINDOW* drawRetryWin(int starty, int startx, int active) {
  refresh();

  WINDOW* win = newwin(RETRY_WIN_HEIGHT, RETRY_WIN_WIDTH, starty, startx);

#define C | A_BOLD
  wborder(win, '|' C, '|' C, '-' C, '-' C, '+' C, '+' C, '+' C, '+' C);

  /* BUTTONS */
  for (int i = 0; i < 3; i++) {
    if (i == active) {
      wattron(win, COLOR_PAIR(retry_colors[i]));
    }

    mvwaddstr(win, 1, retry_xpositions[i], retry_buttons[i]);

    if (i == active) {
      wattroff(win, COLOR_PAIR(retry_colors[i]));
    }
  }

  wrefresh(win);

  return win;
}