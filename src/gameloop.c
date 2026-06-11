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
  checkerFillWindow(viewport, GREEN, DARK_GREEN);

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

  int ch;
  while (true /* not dead */) { // 3 is the key number for ^C
    ch = getch();
    if (ch != -1) { // the user has clicked something
      switch (ch) {
        case KEY_UP:
          SnakeMoveAddSection(snake, DIR_UP);
          break;
        case KEY_RIGHT:
          SnakeMoveAddSection(snake, DIR_RIGHT);
          break;
        case KEY_DOWN:
          SnakeMoveAddSection(snake, DIR_DOWN);
          break;
        case KEY_LEFT:
          SnakeMoveAddSection(snake, DIR_LEFT);
          break;
        case 3: // ^C key or q key
          return;

        default: // unrecognized key
          continue;
      }
    }
    renderSnake(viewport, snake);

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

void renderSnake(WINDOW* win, Snake* snake) {
  snake_t* node = snake->head;

  while (node) {
    mvwaddch(win, node->y, node->x, '=' | COLOR_PAIR(node->color));
    wrefresh(win);

    node = node->next;
  }
}

bool isSnakeDead(WINDOW* win, Snake* snake) {
  return false;
}