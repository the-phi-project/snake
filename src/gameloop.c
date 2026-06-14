#include "gameloop.h"

#include <stdlib.h>
#include <string.h>

#include <ncurses.h>

#include "constants.h"
#include "colors.h"
#include "Snake.h"



void gameloop(int maxy, int maxx, int difficulty) {
  const int diff_dist = ((difficulty == EASY)     ? EASY_BUFFER
                         : (difficulty == NORMAL) ? NORMAL_BUFFER
                                                  : HARD_BUFFER);
  const char* diff_str = ((difficulty == EASY)     ? "EASY"
                          : (difficulty == NORMAL) ? "NORMAL"
                                                   : "HARD");
  const int diff_color = ((difficulty == EASY)     ? EASY_COLOR
                          : (difficulty == NORMAL) ? NORMAL_COLOR
                                                   : HARD_COLOR);

  const int diff_delay = ((difficulty == EASY)     ? 3
                          : (difficulty == NORMAL) ? 2
                                                   : 1);

  /* */


  WINDOW* viewport;
  int starty = (maxy - FULL_ROWS) / 2;
  int startx = (maxx - FULL_COLS) / 2;

  viewport = createGameWindow(starty, startx, FULL_COLS, FULL_ROWS, diff_color);
  fillWindow(viewport, WHITE);

  /* FOOTER */
  wattron(viewport, COLOR_PAIR(diff_color) | A_BOLD);
  mvwprintw(viewport, FULL_ROWS - 1, 2, "The Phi Project - snake    :    V%s - 2026", VERSION);
  wattroff(viewport, COLOR_PAIR(diff_color) | A_BOLD);

  wmove(viewport, 0, 0);
  wrefresh(viewport);
  refresh();
  /* */

  Snake* snake = CreateSnake((FULL_ROWS - 1) / 2, (FULL_COLS - 1) / 2);
  if (!snake) {
    return;
  }

  /* APPLES */
  typedef struct Apple {
    int ticks_alive;
    int lifespan;

    short color;

    struct position pos;

    bool is_alive;
  } Apple;

  int less_than_threshold = RAND_MAX / 4;

  Apple global_apple = { 0, 0, -1, { 0, 0 }, false }; // only the false matters
  /* */

  /* TODO: PROMPT FOR DIFFICULTY ? */

  int score = 0;

  halfdelay(diff_delay); // make sure that the user clicks a key in x/10 seconds

  int ch, dir;
  while (!isSnakeDead(snake)) { // 3 is the key number for ^C
    struct position tail_pos = { snake->tail->y, snake->tail->x };

    ch = getch();
    if (ch != -1) { // the user has clicked something
      switch (ch) {
        // all these ternaries are to ensure you cant go immediately in the opposite direction
        case KEY_UP:
          dir = (dir == DIR_DOWN ? DIR_DOWN : DIR_UP);
          break;
        case KEY_RIGHT:
          dir = (dir == DIR_LEFT ? DIR_LEFT : DIR_RIGHT);
          break;
        case KEY_DOWN:
          dir = (dir == DIR_UP ? DIR_UP : DIR_DOWN);
          break;
        case KEY_LEFT:
          dir = (dir == DIR_RIGHT ? DIR_RIGHT: DIR_LEFT);
          break;
        case 3: // ^C key or q key
          return;

        default: // unrecognized key
          continue;
      }
    }

    MoveSnake(snake, dir);
    renderSnake(viewport, snake);

    // compiler optimized the ternary away pretty much, thank goodness
    // this is where that useful fact below at the checker function comes into play
    mvwaddch(/*
      viewport, tail_pos.y, tail_pos.x,
      ' ' | COLOR_PAIR(((tail_pos.y % 2 == 0) ? ((tail_pos.x % 2 == 0) ? GREEN : DARK_GREEN)
                                              : ((tail_pos.x % 2 == 0) ? DARK_GREEN : GREEN)))*/
      viewport, tail_pos.y, tail_pos.x, ' ' | COLOR_PAIR(WHITE)
    );

    /* */

    if (!global_apple.is_alive && rand() <= less_than_threshold) {
      struct position pos = {
        randomInRange(2, FULL_ROWS - 3),
        randomInRange(2, FULL_COLS - 3)
      };

      int suboptimal = abs(snake->head->y - pos.y) + abs(snake->head->x - pos.x) + diff_dist;

      global_apple.ticks_alive = 0;
      global_apple.lifespan = suboptimal;
      global_apple.color = RED;
      global_apple.pos = pos;
      global_apple.is_alive = true;

      mvwaddch(viewport, pos.y, pos.x, ' ' | COLOR_PAIR(global_apple.color));
    }

    if (global_apple.is_alive) {
      global_apple.ticks_alive++;
      if (global_apple.ticks_alive >= global_apple.lifespan) {
        global_apple.is_alive = false;
        mvwaddch(viewport, global_apple.pos.y, global_apple.pos.x, ' ' | COLOR_PAIR(WHITE));
      } else {
        if (global_apple.pos.y == snake->head->y && global_apple.pos.x == snake->head->x) {
          // no need to clear apple because snake already derenders it
          score += (global_apple.color == RED ? 1 : 3);

          global_apple.is_alive = false;

          SnakeMoveAddSection(snake, dir);
        }
      }
    }

    /* SCORE */
    wattron(viewport, COLOR_PAIR(diff_color) | A_BOLD);
    mvwprintw(viewport, 0, 2, "%d  @ %s", score, diff_str);
    wattroff(viewport, COLOR_PAIR(diff_color) | A_BOLD);
    /* */

    wrefresh(viewport);
    refresh();
  }

  delwin(viewport);
  DestroySnake(snake);
}

WINDOW* createGameWindow(int starty, int startx, int width, int height, short color) {
  refresh();
  WINDOW* local_win = newwin(height, width, starty, startx);

  // creates a border around the window
  int b_ch = ' ' | COLOR_PAIR(color); // border character
  wborder(local_win, b_ch, b_ch, b_ch, b_ch, b_ch, b_ch, b_ch, b_ch);

  wrefresh(local_win);
  return local_win;
}

void fillWindow(WINDOW* win, short color) {
  int height, width;
  getmaxyx(win, height, width);

  for (int row = 1; row < height - 1; row++) {
    for (int col = 1; col < width - 1; col++) {
      mvwaddch(win, row, col, ' ' | COLOR_PAIR(color));
    }
  }

  wrefresh(win);
}

void renderSnake(WINDOW* win, Snake* snake) {
  snake_t* node = snake->head;

  while (node) {
    mvwaddch(win, node->y, node->x, ' ' | COLOR_PAIR(node->color));
    // wrefresh(win);

    node = node->next;
  }
}

bool isSnakeDead(Snake* snake) {
  if (!snake->head) return true;

  bool hit_walls = (
    (snake->head->y <= 0) || (snake->head->y >= FULL_ROWS - 1)) ||
    ((snake->head->x <= 0) || (snake->head->x >= FULL_COLS - 1)
  );

  bool hit_self = false;
  snake_t* node = snake->head->next;
  while (node) {
    if (node->y == snake->head->y && node->x == snake->head->x) {
      hit_self = true;
      break;
    }

    node = node->next;
  }

  return hit_walls || hit_self;
}
