cmake_minimum_required(VERSION 3.22)
project(blackbox)

set(CMAKE_CXX_STANDARD 14)
#add_executable(blackboxdebug tests.cpp include/core/utils.h include/core/database/database.h src/core/utils.cpp src/core/database/database.cpp include/core/client.h src/core/client.cpp)
add_executable(BlackBox main.cpp include/core/utils.h include/core/database/database.h src/core/utils.cpp src/core/database/database.cpp include/core/client.h src/core/client.cpp)
