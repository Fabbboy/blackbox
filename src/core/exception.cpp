
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "../../include/core/exception.h"
#include "../../include/core/colors.h"

void Error(char *msg){
    std::cout << colorize(BLUE) << colorize(UNDERLINE) <<"[" << daytime() << "]" << colorize(RESET) << colorize(RED) << colorize(UNDERLINE) << "[ERROR]" << colorize(RESET) <<" "<< msg << std::endl;
};
void Warning(char *msg){
    std::cout << colorize(BLUE) << colorize(UNDERLINE) <<"[" << daytime() << "]" << colorize(RESET) << colorize(YELLOW) << colorize(UNDERLINE) << "[WARNING]" << colorize(RESET)<<" "<< msg << std::endl;
};
void Info(char *msg){
    std::cout << colorize(BLUE) << colorize(UNDERLINE) <<"[" << daytime() << "]" << colorize(RESET) << colorize(GREEN) << colorize(UNDERLINE) << "[INFO]" << colorize(RESET)<<" "<< msg << std::endl;
};


char* daytime(){
    time_t t = time(nullptr);
    struct tm tm = *localtime(&t);
    char *daytime = (char *) malloc(sizeof(char) * 20);
    sprintf(daytime, "%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    return daytime;
};