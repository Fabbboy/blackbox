#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "../../../include/core/utils.h"
#include <sstream>
#include <vector>

using namespace std;

void initDB(bool debug) {
    //////INIT
    if (!debug) {
        std::cout << "checking setup..." << std::endl;
        char *root = getOsRoot();
        //add "/blackbox/" to root
        char *blackbox_root = (char *) malloc(strlen(root) + strlen("/blackbox/") + 1);
        strcpy(blackbox_root, root);
        strcat(blackbox_root, "/blackbox/");
        //check if blackbox folder exists
        struct stat sb{};
        if (stat(blackbox_root, &sb) == -1) {
            std::cout << "blackbox folder not found" << std::endl;
            if (mkdir(blackbox_root, 0777) == -1) {
                std::cout << "error creating blackbox folder" << std::endl;
                return;
            } else {
                std::cout << "blackbox folder created" << std::endl;
                //create dbs folder
                char *dbs_root = (char *) malloc(strlen(blackbox_root) + strlen("/dbs/") + 1);
                strcpy(dbs_root, blackbox_root);
                strcat(dbs_root, "/dbs/");
                if (mkdir(dbs_root, 0777) == -1) {
                    std::cout << "error creating dbs folder" << std::endl;
                    return;
                } else {
                    std::cout << "dbs folder created" << std::endl;
                }
            }
        } else {
            std::cout << "blackbox folder found" << std::endl;
            //check if dbs folder exists
            char *dbs_root = (char *) malloc(strlen(blackbox_root) + strlen("/dbs/") + 1);
            strcpy(dbs_root, blackbox_root);
            strcat(dbs_root, "/dbs/");
            if (stat(dbs_root, &sb) == -1) {
                std::cout << "dbs folder not found" << std::endl;
                if (mkdir(dbs_root, 0777) == -1) {
                    std::cout << "error creating dbs folder" << std::endl;
                    return;
                } else {
                    std::cout << "dbs folder created" << std::endl;
                }
            } else {
                std::cout << "dbs folder found" << std::endl;
            }
        }
    }else{
        std::cout << "debug mode enabled" << std::endl;
        std::cout << "checking setup..." << std::endl;
        char *root = getOsRoot();
        //add "/blackbox/" to root
        char *blackbox_root = (char *) malloc(strlen(root) + strlen("/blackboxDebug/") + 1);
        strcpy(blackbox_root, root);
        strcat(blackbox_root, "/blackboxDebug/");
        //check if blackbox folder exists
        struct stat sb{};
        if (stat(blackbox_root, &sb) == -1) {
            std::cout << "blackbox folder not found" << std::endl;
            if (mkdir(blackbox_root, 0777) == -1) {
                std::cout << "error creating blackbox folder" << std::endl;
                return;
            } else {
                std::cout << "blackbox folder created" << std::endl;
                //create dbs folder
                char *dbs_root = (char *) malloc(strlen(blackbox_root) + strlen("/dbs/") + 1);
                strcpy(dbs_root, blackbox_root);
                strcat(dbs_root, "/dbs/");
                if (mkdir(dbs_root, 0777) == -1) {
                    std::cout << "error creating dbs folder" << std::endl;
                    return;
                } else {
                    std::cout << "dbs folder created" << std::endl;
                }
            }
        } else {
            std::cout << "blackbox folder found" << std::endl;
            //check if dbs folder exists
            char *dbs_root = (char *) malloc(strlen(blackbox_root) + strlen("/dbs/") + 1);
            strcpy(dbs_root, blackbox_root);
            strcat(dbs_root, "/dbs/");
            if (stat(dbs_root, &sb) == -1) {
                std::cout << "dbs folder not found" << std::endl;
                if (mkdir(dbs_root, 0777) == -1) {
                    std::cout << "error creating dbs folder" << std::endl;
                    return;
                } else {
                    std::cout << "dbs folder created" << std::endl;
                }
            } else {
                std::cout << "dbs folder found" << std::endl;
            }
        }
    }
};



void createDB(char *db_name){
    char* root = getBlackboxRoot(false);
    char* dbRoot = getBlackboxDbsRoot();

    //check if blackbox folder exists.
    if(!checkBlackboxRoot()){
        std::cout << "blackbox folder not found" << std::endl;
        return;
    }
    if(!checkBlackboxDbsRoot()){
        std::cout << "dbs folder not found" << std::endl;
        return;
    }
    if (checkDb(db_name)) {
        std::cout << "db already exists" << std::endl;
        return;
    }else{
        //create db folder
        char* db_folder = (char*)malloc(strlen(dbRoot) + strlen(db_name) + 1);
        strcpy(db_folder, dbRoot);
        strcat(db_folder, db_name);
        if(mkdir(db_folder, 0777) == -1){
            std::cout << "db folder not created" << std::endl;
            return;
        }
    }
};
void dropDB(char* db_name){
    char* root = getBlackboxRoot(false);
    char* dbRoot = getBlackboxDbsRoot();

    //check if blackbox folder exists.
    if(!checkBlackboxRoot()){
        std::cout << "blackbox folder not found" << std::endl;
        return;
    }
    if(!checkBlackboxDbsRoot()){
        std::cout << "dbs folder not found" << std::endl;
        return;
    }
    if (!checkDb(db_name)) {
        std::cout << "db does not exist" << std::endl;
        return;
    }else{
        //delete db folder
        char* db_folder = (char*)malloc(strlen(dbRoot) + strlen(db_name) + 1);
        strcpy(db_folder, dbRoot);
        strcat(db_folder, db_name);
        if(rmdir(db_folder) == -1){
            std::cout << "db folder not deleted" << std::endl;
            return;
        }
    }
};

void createLayer(char *db_name, char *layer_name){
    //table called layer_name.bb
    char* root = getBlackboxRoot(false);
    char* dbRoot = getBlackboxDbsRoot();

    if(!checkBlackboxRoot()){
        std::cout << "blackbox folder not found" << std::endl;
        return;
    }
    if(!checkBlackboxDbsRoot()){
        std::cout << "dbs folder not found" << std::endl;
        return;
    }
    if (!checkDb(db_name)) {
        std::cout << "db does not exist" << std::endl;
        return;
    }else{
        //create layer file
        char* layer_file = (char*)malloc(strlen(dbRoot) + strlen(db_name) + strlen("/") + strlen(layer_name) + strlen(".bb") + 1);
        strcpy(layer_file, dbRoot);
        strcat(layer_file, db_name);
        strcat(layer_file, "/");
        strcat(layer_file, layer_name);
        strcat(layer_file, ".bb");
        if(access(layer_file, F_OK) != -1){
            std::cout << "layer already exists" << std::endl;
            return;
        }else{
            FILE* fp = fopen(layer_file, "w");
            fclose(fp);
        }
    }
};
void dropLayer(char *db_name, char *layer_name){
    //table called layer_name.bb
    char* root = getBlackboxRoot(false);
    char* dbRoot = getBlackboxDbsRoot();

    if(!checkBlackboxRoot()){
        std::cout << "blackbox folder not found" << std::endl;
        return;
    }
    if(!checkBlackboxDbsRoot()){
        std::cout << "dbs folder not found" << std::endl;
        return;
    }
    if (!checkDb(db_name)) {
        std::cout << "db does not exist" << std::endl;
        return;
    }else{
        //create layer file
        char* layer_file = (char*)malloc(strlen(dbRoot) + strlen(db_name) + strlen("/") + strlen(layer_name) + strlen(".bb") + 1);
        strcpy(layer_file, dbRoot);
        strcat(layer_file, db_name);
        strcat(layer_file, "/");
        strcat(layer_file, layer_name);
        strcat(layer_file, ".bb");
        if(access(layer_file, F_OK) != -1){
            if(remove(layer_file) == -1){
                std::cout << "layer not deleted" << std::endl;
                return;
            }
        }else{
            std::cout << "layer does not exist" << std::endl;
            return;
        }
    }
};

//key=value


//insert key char* value char*
void insert(char *db_name, char *layer_name, char *key, char *value){
    char* root = getBlackboxRoot(false);
    char* dbRoot = getBlackboxDbsRoot();

    if(!checkBlackboxRoot()){
        std::cout << "blackbox folder not found" << std::endl;
        return;
    }
    if(!checkBlackboxDbsRoot()){
        std::cout << "dbs folder not found" << std::endl;
        return;
    }
    if (!checkDb(db_name)) {
        std::cout << "db does not exist" << std::endl;
        return;
    }else{
        if(checkLayer(db_name, layer_name)) {
            //read everything line by line into a std::vector<std::string> change strings as necessary and write the whole stuff back.
            std::vector<std::string> lines;
            char* layer_file = (char*)malloc(strlen(dbRoot) + strlen(db_name) + strlen("/") + strlen(layer_name) + strlen(".bb") + 1);
            strcpy(layer_file, dbRoot);
            strcat(layer_file, db_name);
            strcat(layer_file, "/");
            strcat(layer_file, layer_name);
            strcat(layer_file, ".bb");
            std::ifstream file(layer_file);
            std::string line;
            while (std::getline(file, line)) {
                lines.push_back(line);
            }
            file.close();
            //check if key already exists
            bool key_exists = false;
            for(auto & line : lines){
                if(line.find(key) != std::string::npos){
                    key_exists = true;
                    std::ostringstream oss;
                    oss << key << "=" << value;
                    line = oss.str();
                }
            }
            if(!key_exists){
                std::ostringstream oss;
                oss << key << "=" << value;
                lines.push_back(oss.str());
            }
            //write back to file
            std::ofstream file2(layer_file);
            for(auto & line : lines){
                file2 << line << std::endl;
            }
            file2.close();
        }else{
            std::cout << "layer does not exist" << std::endl;
            return;
        }
    }
};
//TODO insert array

char* get(char *db_name, char *layer_name, char *key);
//TODO get array

void remove(char *db_name, char *layer_name, char *key);

//list all
char** list(char *db_name, char *layer_name);