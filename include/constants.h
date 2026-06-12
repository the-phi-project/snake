#ifndef SNAKE_CONSTANTS_H
#define SNAKE_CONSTANTS_H

#define FULL_ROWS 22  // header, game, footer
#define FULL_COLS 50  // size border, game, side border

#define DIR_UP 0
#define DIR_RIGHT 1
#define DIR_DOWN 2
#define DIR_LEFT 3

#define EASY 0
#define NORMAL 1
#define HARD 2

#include "colors.h"
#define EASY_COLOR WHITE_GREEN
#define NORMAL_COLOR WHITE_CYAN
#define HARD_COLOR WHITE_GOLD

// to be added to distance for apple lifespan
#define EASY_BUFFER 7
#define NORMAL_BUFFER 5
#define HARD_BUFFER 3

#include <stdlib.h>

inline int randomInRange(int min, int max) {
  return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

inline int max(int a, int b) {
  return (a > b ? a : b);
}

#endif /* SNAKE_CONSTANTS_H */