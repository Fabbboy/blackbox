#include "../../include/core/colors.h"

const char * colorize(Color color){
    switch(color){
        case BLACK:
            return "\033[30m";
        case RED:
            return "\033[31m";
        case GREEN:
            return "\033[32m";
        case YELLOW:
            return "\033[33m";
        case BLUE:
            return "\033[34m";
        case MAGENTA:
            return "\033[35m";
        case CYAN:
            return "\033[36m";
        case WHITE:
            return "\033[37m";
        case RESET:
            return "\033[0m";
        case BOLD:
            return "\033[1m";
        case UNDERLINE:
            return "\033[4m";
        default:
            return "";
    }
};
