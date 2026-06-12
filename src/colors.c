#include "colors.h"

#include <ncurses.h>

void initColors() {/*
  if (can_change_color()) { // ALL OF THOSE THIRD NUMBERS ARE MAGIC NUMBERS FOR 8-BIT COLORS
    init_pair(GREEN, COLOR_BLACK, 22);

    init_pair(DARK_GREEN, COLOR_BLACK, 5);

    init_pair(RED, COLOR_BLACK, 160);
    
    init_pair(GOLD, COLOR_BLACK, 178);
    
    init_pair(CYAN, COLOR_BLACK, 159);
    
    init_pair(WHITE_CYAN, 240, 159); // gray - cyan
    
    init_pair(BLUE, COLOR_BLACK, 17);
    
    init_pair(VIOLET, COLOR_BLACK, 56);
  } else {
    init_pair(GREEN, COLOR_BLACK, COLOR_GREEN);

    init_pair(DARK_GREEN, COLOR_BLACK, COLOR_GREEN);

    init_pair(RED, COLOR_BLACK, COLOR_RED);

    init_pair(GOLD, COLOR_BLACK, COLOR_YELLOW);

    init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);

    init_pair(WHITE_CYAN, COLOR_WHITE, COLOR_CYAN);

    init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);

    init_pair(VIOLET, COLOR_BLACK, COLOR_MAGENTA);
  }*/

  init_pair(RED, COLOR_BLACK, COLOR_RED);

  init_pair(GOLD, COLOR_BLACK, COLOR_YELLOW);

  init_pair(CYAN, COLOR_BLACK, COLOR_CYAN);

  init_pair(WHITE_CYAN, COLOR_WHITE, COLOR_CYAN);

  init_pair(BLUE, COLOR_BLACK, COLOR_BLUE);

  init_pair(VIOLET, COLOR_BLACK, COLOR_MAGENTA);

  init_pair(WHITE, COLOR_WHITE, COLOR_WHITE);
  
  init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
}