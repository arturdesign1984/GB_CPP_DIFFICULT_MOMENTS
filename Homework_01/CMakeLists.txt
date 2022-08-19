cmake_minimum_required(VERSION 3.0.0)
project(HW VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.cpp)
add_custom_command(
        TARGET  ${PROJECT_NAME} POST_BUILD 
        COMMAND ${CMAKE_COMMAND} -E copy 
                ${CMAKE_CURRENT_SOURCE_DIR}/PhoneBook.txt
                ${CMAKE_CURRENT_BINARY_DIR}/PhoneBook.txt)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_CXX_STANDARD 20)
include(CPack)