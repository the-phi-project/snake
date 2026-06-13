#ifndef SNAKE_COLORS_H
#define SNAKE_COLORS_H

#include <ncurses.h>



#define GREEN 1
#define WHITE_GREEN 2
#define RED 3
#define WHITE_RED 4
#define GOLD 5
#define WHITE_GOLD 6
#define CYAN 7
#define WHITE_CYAN 8
#define BLUE 9
#define VIOLET 10
#define WHITE 11
#define BLACK 12

/// This uses "inverted" color pairs because the game
/// can then use the space (' ') character with the
/// background as a color instead of using a unicode
/// character which requires a separate library
void initColors();


#endif /* SNAKE_COLORS_H */