cmake_minimum_required(VERSION 3.10)

project(QueueExercise)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Catch2 as a subdirectory.
add_subdirectory(Catch2)

# Create an executable for tests.
add_executable(queue_tests main_tests.cpp)
# Create an executable for main.
add_executable(queue_main main.cpp)

# Link the Catch2 library with test target.
target_link_libraries(queue_tests PRIVATE Catch2::Catch2WithMain)