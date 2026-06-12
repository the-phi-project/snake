#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <stdlib.h>
#include <stdbool.h>

#include "colors.h"
#include "constants.h"



typedef struct snake_t {
  int color;

  int y;
  int x;

  struct snake_t* prev;
  struct snake_t* next;
} snake_t;

typedef struct Snake {
  struct snake_t* head;
  struct snake_t* tail;
} Snake;

struct position {
    int y;
    int x;
};


Snake* CreateSnake(int starty, int startx);

void SnakeMoveAddSection(Snake* snake, int direction);

void DestroySnake(Snake* snake);

/// returns whether the snake has died or not
void MoveSnake(Snake* snake, int direction);


#endif /* SNAKE_SNAKE_H */