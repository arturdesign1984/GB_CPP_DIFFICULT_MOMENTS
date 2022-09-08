cmake_minimum_required(VERSION 3.0.0)
project(HW VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

# Setup testing
add_subdirectory(gt)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Exe
add_executable(${PROJECT_NAME} main.cpp)

# Copy file to the build dir
add_custom_command(
        TARGET  ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy 
                ${CMAKE_CURRENT_SOURCE_DIR}/PhoneBook.txt
                ${CMAKE_CURRENT_BINARY_DIR}/PhoneBook.txt)

# Link test executable against gtest & gtest_main
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
