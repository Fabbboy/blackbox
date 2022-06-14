#ifndef BLACKBOX_DATABASE_H
#define BLACKBOX_DATABASE_H

void initDB(bool debug);

void createDB(char *db_name);
void dropDB(char* db_name);

void createLayer(char *db_name, char *layer_name);
void dropLayer(char *db_name, char *layer_name);

//insert key char* value char*
void insert(char *db_name, char *layer_name, char *key, char *value);
//TODO insert array

char* get(char *db_name, char *layer_name, char *key);
//TODO get array

void removeKey(char *db_name, char *layer_name, char *key);



#endif //BLACKBOX_DATABASE_H
