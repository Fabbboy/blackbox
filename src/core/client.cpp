#include <iostream>
#include <unistd.h>
#include "../../include/core/client.h"
#include "../../include/core/utils.h"

//function to handle clients
void handleClient(int client_fd){
    //read message from client
    char message[1024];
    int n = read(client_fd, message, 1024);
    if (n < 0) {
        std::cout << "read error" << std::endl;
        return;
    }
    //if client disconnects or lost connect delete thread
    if (n == 0) {
        std::cout << "client disconnected" << std::endl;
        close(client_fd);
        pthread_exit(NULL);
    }
    std::cout << "Message from client: " << message << std::endl;
};