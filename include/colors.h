#ifndef SNAKE_COLORS_H
#define SNAKE_COLORS_H

#include <ncurses.h>

#define GREEN 1
#define DARK_GREEN 2
#define RED 3
#define GOLD 4
#define CYAN 5
#define WHITE_CYAN 6
#define BLUE 7
#define VIOLET 8

/// This uses "inverted" color pairs because the game
/// can then use the space (' ') character with the
/// background as a color instead of using a unicode
/// character which requires a separate library
void initColors() {
  init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);
  init_pair(RED, COLOR_BLACK, COLOR_RED);
  init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);
  init_pair(WHITE_CYAN, COLOR_WHITE, COLOR_CYAN);
  init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);

  if (can_change_color()) {
    // so sorry for all the magic numbers
    init_color(COLOR_MAGENTA, 90, 224, 47); // change to dark green - scaled from (23,57,12)
    init_color(COLOR_YELLOW, 690, 498, 59); // change to gold - scaled from (176,127,15)
    init_color(200, 706, 412, 929); // create new violet color - scaled from (180,105,237)

    init_pair(DARK_GREEN, COLOR_BLACK, COLOR_MAGENTA); // green or dark green depending
    init_pair(VIOLET, COLOR_BLACK, 200); // green or dark green depending
  } else {
    init_pair(DARK_GREEN, COLOR_BLACK, COLOR_GREEN);  //  ^^^^^^^^
    init_pair(VIOLET, COLOR_BLACK, COLOR_BLUE);  //  ^^^^^^^^
  }
  
  /* its okay to change and then use COLOR_YELLOW because its not used elsewhere
     changing a color changes it permanentely, like changing COLOR_GREEN just for 
     the use of DARK_GREEN also changes the color for earlier-defined pairs */
  init_pair(GOLD, COLOR_BLACK, COLOR_YELLOW); // yellow or gold depending
}

#endif /* SNAKE_COLORS_H */