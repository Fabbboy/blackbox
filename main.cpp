#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <unistd.h>
#include "include/core/client.h"
#include "include/core/utils.h"
#include "include/core/database/database.h"


int main() {

    initDB(false);


    //init socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        std::cout << "socket error" << std::endl;
        return -1;
    }
    //run socket on localhost:7769
    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(7769);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cout << "bind error" << std::endl;
        return -1;
    }

    std::cout << "binded localhost:7769" << std::endl;
    //listen for infinity and for every connection make a new thread
    while (1) {
        if (listen(sockfd, 5) < 0) {
            std::cout << "listen error" << std::endl;
            return -1;
        }
        struct sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
        int client_fd = accept(sockfd, (struct sockaddr *) &client_addr, &client_addr_len);
        if (client_fd < 0) {
            std::cout << "accept error" << std::endl;
            return -1;
        }
        pthread_t thread;
        //run handleClient in thread
        pthread_create(&thread, nullptr, (void *(*)(void *)) handleClient, (void *) client_fd);
    }
    return 0;
}

