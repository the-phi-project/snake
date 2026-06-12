#ifndef SNAKE_GAMELOOP_H
#define SNAKE_GAMELOOP_H

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "constants.h"
#include "colors.h"
#include "Snake.h"



void gameloop(int maxy, int maxx, int difficulty);

WINDOW* createGameWindow(int starty, int startx, int width, int height, short color);

void fillWindow(WINDOW* win, short color);

void renderSnake(WINDOW* win, Snake* snake);

bool isSnakeDead(Snake* snake);


#endif /* SNAKE_GAMELOOP_H */