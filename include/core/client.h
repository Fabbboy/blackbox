
#ifndef BLACKBOX_CLIENT_H
#define BLACKBOX_CLIENT_H

enum PackageType {
    CREATE_DB = 1,
    DROP_DB = 2,
    CREATE_LAYER = 3,
    DROP_LAYER = 4,
    INSERT = 5,
    GET = 6,
    REMOVE_KEY = 7,
    QUIT = 8,
    UNKNOWN = 9
};

//function to handle clients
void handleClient(int client_fd);
void identifyPackage(int client_fd, char *message);

#endif //BLACKBOX_CLIENT_H
