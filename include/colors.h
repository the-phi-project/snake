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
void initColors();


#endif /* SNAKE_COLORS_H */