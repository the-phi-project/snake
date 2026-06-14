#ifndef SNAKE_RETRY_H
#define SNAKE_RETRY_H

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "colors.h"
#include "constants.h"

#define RETRY_WIN_HEIGHT 3
#define RETRY_WIN_WIDTH 29


int retry(int maxy, int maxx);

WINDOW* drawRetryWin(int starty, int startx, int active);

#endif /* SNAKE_RETRY_H */
