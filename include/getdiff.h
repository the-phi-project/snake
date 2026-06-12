#ifndef SNAKE_GETDIFF_H
#define SNAKE_GETDIFF_H

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "colors.h"
#include "constants.h"

#define WIN_HEIGHT 5
#define WIN_WIDTH 23


int getdiff(int maxy, int maxx);

WINDOW* drawGetDiffWin(int starty, int startx, int active);

#endif /* SNAKE_GETDIFF_H */
