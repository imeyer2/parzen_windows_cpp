cmake_minimum_required(VERSION 3.10)
project(YourPackageName VERSION 1.0)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add header files
include_directories(include)

# Can manually add source files or use file(GLOB ...) to select all cpp files in src/
add_library(parzen_windows SHARED
    src/base_pdf_generator.cpp
)

# For an executable instead of a library, use add_executable() instead of add_library()

# Specify installation rules
install(TARGETS parzen_windows DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)


# Create example executable
add_executable(example_exec src/example.cpp src/base_pdf_generator.cpp)
