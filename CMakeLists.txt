cmake_minimum_required(VERSION 3.10)
project(parzen_windows VERSION 1.0)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add header files
include_directories(include)
include_directories(/opt/homebrew/include/gtest)

# Find Google Test (corrected path)
find_package(GTest REQUIRED PATHS /opt/homebrew/include/gtest)  # Adjust the path as needed

# Create the library
add_library(parzen_windows SHARED src/base_pdf_generator.cpp src/base_kernel_functions.cpp)

# Enable testing
enable_testing()

# Create the test executable
add_executable(parzen_windows_tests tests/base_pdf_generator_test.cpp)
target_link_libraries(
    parzen_windows_tests
    GTest::gtest_main
)
# Link the test executable with the library and Google Test
target_link_libraries(parzen_windows_tests parzen_windows ${GTest_LIBRARIES})

# Specify installation rules
install(TARGETS parzen_windows DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)


# Create example executable (optional)
add_executable(example_exec src/example.cpp) 
target_link_libraries(example_exec parzen_windows)


# Create visualization example
add_executable(example_exec2 src/example2.cpp) 
target_link_libraries(example_exec2 parzen_windows)

# https://alandefreitas.github.io/matplotplusplus/integration/cmake/embed-as-subdirectory/