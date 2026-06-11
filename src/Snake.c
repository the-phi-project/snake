#include "Snake.h"

#include <stdlib.h>

#include "colors.h"
#include "constants.h"



Snake* CreateSnake(int starty, int startx) {
  Snake* snake = malloc(sizeof(*snake));
  snake_t* head = malloc(sizeof(*head));
  if (!head) {
    free(snake);
    return NULL;
  }

  head->color = VIOLET;
  head->y = starty;
  head->x = startx;
  head->prev = NULL;
  head->next = NULL;

  snake->head = head;
  snake->tail = head;

  return snake;
}

void SnakeMoveAddSection(Snake* snake, int direction) {
  if (!snake->tail) return;

  snake_t* new_section = malloc(sizeof(*new_section));
  if (!new_section) return;
  
  new_section->prev = snake->tail;
  new_section->next = NULL;
  new_section->color = BLUE;
  
  new_section->y = snake->tail->y;
  new_section->x = snake->tail->x;

  // the new section will take the place of the tail before the snake knows it exists
  MoveSnake(snake, direction);

  snake->tail->next = new_section;
  snake->tail = new_section;
}

void DestroySnake(Snake* snake) {
  while (snake->head != snake->tail) {
    snake_t* new_tail = snake->tail->prev;
    free(snake->tail);
    snake->tail = new_tail;
  }

  free(snake->head);
  free(snake);
}

void MoveSnake(Snake* snake, int direction) {
  snake_t* node = snake->head;
  if (!node) return;

  int y1 = node->y, x1 = node->x;
  int y2, x2;

  switch (direction) {
    case DIR_UP:
      snake->head->y--;
      break;
    case DIR_RIGHT:
      snake->head->x++;
      break;
    case DIR_DOWN:
      snake->head->y++;
      break;
    case DIR_LEFT:
      snake->head->x--;
      break;
  }

  node = snake->head->next;

  // there has GOT to be a better way to do this
  while (node) {
    y2 = node->y;
    x2 = node->x;

    node->y = y1;
    node->x = x1;

    y1 = y2;
    x1 = x2;

    node = node->next;
  }
}