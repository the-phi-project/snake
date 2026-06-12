#include "gameloop.h"

#include <stdlib.h>

#include <ncurses.h>

#include "constants.h"
#include "colors.h"
#include "Snake.h"



void gameloop(int maxy, int maxx) {
  WINDOW* viewport;
  int starty = (maxy - FULL_ROWS) / 2;
  int startx = (maxx - FULL_COLS) / 2;

  viewport = createGameWindow(starty, startx, FULL_COLS, FULL_ROWS);
  //checkerFillWindow(viewport, GREEN, DARK_GREEN);
  fillWindow(viewport, WHITE);

  /* FOOTER */
  wattron(viewport, COLOR_PAIR(WHITE_CYAN) | A_BOLD);
  mvwprintw(viewport, FULL_ROWS - 1, 2, "The Phi Project - snake    :    V%s - 2026", VERSION);
  wattroff(viewport, COLOR_PAIR(WHITE_CYAN) | A_BOLD);

  wmove(viewport, 0, 0);
  wrefresh(viewport);
  refresh();
  /* */

  Snake* snake = CreateSnake((FULL_ROWS - 1) / 2, (FULL_COLS - 1) / 2);
  if (!snake) {
    return;
  }

  /* TODO: PROMPT FOR DIFFICULTY ? */

  halfdelay(2); // make sure that the user clicks a key in 2/10 seconds

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

    wrefresh(viewport);
    refresh();
  }

  DestroySnake(snake);
}

WINDOW* createGameWindow(int starty, int startx, int width, int height) {
  refresh();
  WINDOW* local_win = newwin(height, width, starty, startx);
  
  // creates a border around the window
  int b_ch = ' ' | COLOR_PAIR(CYAN); // border character
  wborder(local_win, b_ch, b_ch, b_ch, b_ch, b_ch, b_ch, b_ch, b_ch);

  wrefresh(local_win);
  return local_win;
}

/*
This function means that on all ODD rows, all EVEN columns are color2
and on all EVEN rows, all ODD columns are color2

(this fun fact is useful above when clearing the snake's tail's position)
*/
/*
void checkerFillWindow(WINDOW* win, short color1, short color2) {
  int height, width;
  getmaxyx(win, height, width);

  int ch = ' ';
  bool col1 = true;
  for (int row = 1; row < height - 1; row++) { // start below header and end above footer
    for (int col = 1; col < width - 1; col++) { // go from inside one border to the other
      mvwaddch(win, row, col, ch | (col1 ? COLOR_PAIR(color1) : COLOR_PAIR(color2)));
      col1 = !col1;
    }

    col1 = !col1; // staggers it in a checker pattern
  }

  wmove(win, 0, 0);
  wrefresh(win);
}
*/
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
  return ((snake->head->y <= 0) || (snake->head->y >= FULL_ROWS)) || ((snake->head->x <= 0) || (snake->head->x >= FULL_COLS));
}