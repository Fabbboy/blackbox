#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include "include/core/client.h"
#include "include/core/database/database.h"
#include "include/core/exception.h"
#include "include/core/utils.h"


int main() {

    initDB(false);


    //init socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        Error("socket error");
        return -1;
    }
    //run socket on localhost:7769
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7769);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        Error("bind error");
        return -1;
    }

    Info("binded localhost:7769");
    char* databaseMessaeg = "Database is located at: ";
    char* databasePath = getBlackboxRoot(false);
    //add database path to message
    char* databasePathMessage = (char *) malloc(strlen(databasePath) + strlen(databaseMessaeg) + 1);
    strcpy(databasePathMessage, databaseMessaeg);
    strcat(databasePathMessage, databasePath);
    Info(databasePathMessage);
    free(databasePathMessage);
    //listen for infinity and for every connection make a new thread
    while (1) {
        if (listen(sockfd, 5) < 0) {
            Error("listen error");
            return -1;
        }
        struct sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd < 0) {
            Error("accept error");
            return -1;
        }
        //new client connect
        char* clientIp = inet_ntoa(client_addr.sin_addr);
        char* clientIpandText = (char *) malloc(strlen(clientIp) + 1);
        strcpy(clientIpandText, "new client connected: ");
        strcpy(clientIpandText, clientIp);
        Info(clientIpandText);
        pthread_t thread;
        //run handleClient in thread
        pthread_create(&thread, nullptr, (void *(*)(void *)) handleClient, (void *) client_fd);
    }
    return 0;
}

