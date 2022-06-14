#include <iostream>
#include "include/core/database/database.h"

int main(){
    initDB(true);
    createDB("testDB");
    createLayer("testDB", "testLayer");
}