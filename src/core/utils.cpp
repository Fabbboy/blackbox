#include <iostream>
#include <unistd.h>
#include <sys/stat.h>

void writeToClient(int client_fd, const char *message){
    //write message to client
    int n = write(client_fd, message, strlen(message));
    if (n < 0) {
        std::cout << "write error" << std::endl;
        return;
    }
};

char* getOsRoot(){
    //get os root. Example: /home/user or C:/
    char *root = getenv("HOME");
    return root;
};
char* getBlackboxRoot(bool debug){
    //get blackbox root. Example: /home/user/blackbox or C:/blackbox
    if(!debug) {
        char *root = getOsRoot();
        char *blackbox_root = (char *) malloc(strlen(root) + strlen("/blackbox/") + 1);
        strcpy(blackbox_root, root);
        strcat(blackbox_root, "/blackbox/");
        //check if blackbox fodler exists if not return false else return true
        struct stat sb{};
        if (stat(blackbox_root, &sb) == -1) {
            return NULL;
        } else {
            return blackbox_root;
        }
    }else{
        char *root = getOsRoot();
        char *blackbox_root = (char *) malloc(strlen(root) + strlen("/blackboxDebug/") + 1);
        strcpy(blackbox_root, root);
        strcat(blackbox_root, "/blackboxDebug/");
        //check if blackbox fodler exists if not return false else return true
        struct stat sb{};
        if (stat(blackbox_root, &sb) == -1) {
            return NULL;
        } else {
            return blackbox_root;
        }
    }
};

bool checkBlackboxRoot(){
    char* root = getOsRoot();
    char* blackbox_root = (char*)malloc(strlen(root) + strlen("/blackbox/") + 1);
    strcpy(blackbox_root, root);
    strcat(blackbox_root, "/blackbox/");
    //check if blackbox fodler exists if not return false else return true
    struct stat sb{};
    if (stat(blackbox_root, &sb) == -1) {
        return false;
    }else{
        return true;
    }
};

char* getBlackboxDbsRoot(){
    //get blackbox dbs root. Example: /home/user/blackbox/dbs or C:/blackbox/dbs
    char* root = getBlackboxRoot(false);
    char* dbs_root = (char*)malloc(strlen(root) + strlen("dbs/") + 1);
    strcpy(dbs_root, root);
    strcat(dbs_root, "dbs/");
    //check if dbs folder exists if not return false else return true
    struct stat sb{};
    if (stat(dbs_root, &sb) == -1) {
        return nullptr;
    }else{
        return dbs_root;
    }
};
bool checkBlackboxDbsRoot(){
    char* root = getBlackboxRoot(false);
    char* dbs_root = (char*)malloc(strlen(root) + strlen("/dbs/") + 1);
    strcpy(dbs_root, root);
    strcat(dbs_root, "/dbs/");
    //check if dbs folder exists if not return false else return true
    struct stat sb{};
    if (stat(dbs_root, &sb) == -1) {
        return false;
    }else{
        return true;
    }
};
bool checkDb(char *db_name){
    //check if db exists if not return false else return true
    char* root = getBlackboxDbsRoot();
    char* db_root = (char*)malloc(strlen(root) + strlen(db_name) + strlen("/") + 1);
    strcpy(db_root, root);
    strcat(db_root, db_name);
    strcat(db_root, "/");
    struct stat sb{};
    if (stat(db_root, &sb) == -1) {
        return false;
    }else{
        return true;
    }
};

//layers are files with .bb at the end
bool checkLayer(char *db_name, char *layer_name){
    //check if layer exists if not return false else return true
    char* root = getBlackboxDbsRoot();
    char* db_root = (char*)malloc(strlen(root) + strlen(db_name) + strlen("/") + 1);
    strcpy(db_root, root);
    strcat(db_root, db_name);
    strcat(db_root, "/");
    char* layer_root = (char*)malloc(strlen(db_root) + strlen(layer_name) + strlen(".bb") + 1);
strcpy(layer_root, db_root);
strcat(layer_root, layer_name);
strcat(layer_root, ".bb");
    struct stat sb{};
    if (stat(layer_root, &sb) == -1) {
        return false;
    }else{
        return true;
    }
};
char* getLayerPath(char *db_name, char *layer_name){
    //get layer path. Example: /home/user/blackbox/dbs/db_name/layer_name.bb
    char* root = getBlackboxDbsRoot();
    char* db_root = (char*)malloc(strlen(root) + strlen(db_name) + strlen("/") + 1);
    strcpy(db_root, root);
    strcat(db_root, db_name);
    strcat(db_root, "/");
    char* layer_root = (char*)malloc(strlen(db_root) + strlen(layer_name) + strlen(".bb") + 1);
strcpy(layer_root, db_root);
strcat(layer_root, layer_name);
strcat(layer_root, ".bb");
    return layer_root;
};


char* getLayerTempPath(char *db_name, char *layer_name){
    char* root = getBlackboxDbsRoot();
    char* db_root = (char*)malloc(strlen(root) + strlen(db_name) + strlen("/") + 1);
    strcpy(db_root, root);
    strcat(db_root, db_name);
    strcat(db_root, "/");
    char* layer_root = (char*)malloc(strlen(db_root) + strlen(layer_name) + strlen(".bb") + 1);
    strcpy(layer_root, db_root);
    strcat(layer_root, layer_name);
    strcat(layer_root, "Temp");
    strcat(layer_root, ".bb");
    return layer_root;
};