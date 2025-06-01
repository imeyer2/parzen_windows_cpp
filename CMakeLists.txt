cmake_minimum_required(VERSION 3.20)
project(parzen_windows_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# -O3 because we are looking for the fastest code
# -march=native because we want to use the best optimizations for the current architecture
add_compile_options(-O3 -march=native -pipe) 

# include the third_party directory which has 3rd party libraries
include_directories(include third_party)

# tell CMake where to find the source files
add_executable(parzen_server
    src/server.cpp
    src/csv_reader.cpp
    src/kde.cpp
)

find_package(Threads REQUIRED)

# target_link_libraries is used here because
# we need to link the threads library to our executable
# we use PRIVATE to avoid exposing this dependency to other targets
target_link_libraries(parzen_server PRIVATE Threads::Threads)
