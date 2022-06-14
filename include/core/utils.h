
#ifndef BLACKBOX_UTILS_H
#define BLACKBOX_UTILS_H
void writeToClient(int client_fd, const char *message);
char* getOsRoot();
char* getBlackboxRoot(bool debug);
bool checkBlackboxRoot();

char* getBlackboxDbsRoot();
bool checkBlackboxDbsRoot();

bool checkDb(char *db_name);
bool checkLayer(char *db_name, char *layer_name);
char* getLayerPath(char *db_name, char *layer_name);
char* getLayerTempPath(char *db_name, char *layer_name);

#endif //BLACKBOX_UTILS_H
