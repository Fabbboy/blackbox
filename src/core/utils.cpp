#include <iostream>
#include <unistd.h>

void writeToClient(int client_fd, const char *message){
    //write message to client
    int n = write(client_fd, message, strlen(message));
    if (n < 0) {
        std::cout << "write error" << std::endl;
        return;
    }
};