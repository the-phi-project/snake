#ifndef SNAKE_COLORS_H
#define SNAKE_COLORS_H

#include <ncurses.h>



#define GREEN 1
#define WHITE_GREEN 2
#define RED 3
#define GOLD 4
#define WHITE_GOLD 5
#define CYAN 6
#define WHITE_CYAN 7
#define BLUE 8
#define VIOLET 9
#define WHITE 10
#define BLACK 11

/// This uses "inverted" color pairs because the game
/// can then use the space (' ') character with the
/// background as a color instead of using a unicode
/// character which requires a separate library
void initColors();


#endif /* SNAKE_COLORS_H */