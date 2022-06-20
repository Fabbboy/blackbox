

#ifndef BLACKBOX_COLORS_H
#define BLACKBOX_COLORS_H

enum Color {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7,
    RESET = 8,
    BOLD = 9,
    UNDERLINE = 10,
};
const char * colorize(Color color);

#endif //BLACKBOX_COLORS_H
