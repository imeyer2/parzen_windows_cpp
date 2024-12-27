cmake_minimum_required(VERSION 3.10)
project(parzen_windows VERSION 1.0)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Add header files
include_directories(include)

# Create the library
add_library(parzen_windows SHARED src/*.cpp)

# Create the test executable
add_executable(parzen_windows_tests tests/base_pdf_generator_test.cpp)

# Find Google Test
find_package(GTest REQUIRED)

# Link the test executable with the library and Google Test
target_link_libraries(parzen_windows_tests parzen_windows ${GTest_LIBRARIES})

# Specify installation rules
install(TARGETS parzen_windows DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Create example executable (optional)
add_executable(example_exec src/example.cpp) 
target_link_libraries(example_exec parzen_windows)