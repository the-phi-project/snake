#ifndef SNAKE_GAMELOOP_H
#define SNAKE_GAMELOOP_H

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "constants.h"
#include "colors.h"
#include "Snake.h"



void gameloop(int maxy, int maxx);

WINDOW* createGameWindow(int starty, int startx, int width, int height);

void checkerFillWindow(WINDOW* win, short color1, short color2);

void renderSnake(WINDOW* win, Snake* snake);

bool isSnakeDead(WINDOW* win, Snake* snake);


#endif /* SNAKE_GAMELOOP_H */