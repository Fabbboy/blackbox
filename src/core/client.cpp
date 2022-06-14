#include <iostream>
#include <unistd.h>
#include "../../include/core/client.h"
#include "../../include/core/utils.h"
#include "../../include/core/database/database.h"

//function to handle clients
void handleClient(int client_fd){
    //read client's full message
    int readBytes = 1024;
    char buffer[readBytes];
    int n = read(client_fd, buffer, readBytes);
    if (n < 0) {
        std::cout << "read error" << std::endl;
        return;
    }
    //get client's message
    char *message = (char *) malloc(strlen(buffer) + 1);
    strcpy(message, buffer);
    //get client's command
    char *command = (char *) malloc(strlen(message) + 1);
    strcpy(command, message);

    identifyPackage(client_fd, command);


    //if client disconnects or lost connect delete thread
    if (n == 0) {
        std::cout << "client disconnected" << std::endl;
        close(client_fd);
        pthread_exit(nullptr);
    }
};
void identifyPackage(int client_fd, char* message){
    //split string with -.example: hello-world -> hello world
    //array
    char *array[1000];
    //splut by - and put word in array
    char *token = strtok(message, "-");
    int i = 0;
    while (token != nullptr) {
        array[i] = token;
        token = strtok(nullptr, "-");
        i++;
    }
    //check if ddb or dbl
    if (strcmp(array[0], "cdb") == 0) {
        //run database functipn
        createDB(array[1]);
    } else if (strcmp(array[0], "ddb") == 0) {
        //run database functipn
        dropDB(array[1]);
    } else if (strcmp(array[0], "cl") == 0) {
        //run database functipn
        createLayer(array[1], array[2]);
    } else if (strcmp(array[0], "dl") == 0) {
        //run database functipn
        dropLayer(array[1], array[2]);
    } else if (strcmp(array[0], "i") == 0) {
        //run database functipn
        insert(array[1], array[2], array[3], array[4]);
    } else if (strcmp(array[0], "g") == 0) {
        //run database functipn
        writeToClient(client_fd,get(array[1], array[2], array[3]));
    } else if (strcmp(array[0], "rk") == 0) {
        //run database functipn
        removeKey(array[1], array[2], array[3]);
    } else if (strcmp(array[0], "q") == 0) {
        //disconncet client
        close(client_fd);
    } else {
        //run database functipn
        return;
    }
};