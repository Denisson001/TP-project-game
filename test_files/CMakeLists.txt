cmake_minimum_required(VERSION 2.8) 

set(PROJECT_NAME "tests")
set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib_files)
project(${PROJECT_NAME})

link_directories(${LIB_FILES_PATH}/SFML/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCES_LIST "${SOURCE_FILES_PATH}/tests.cpp")

add_executable(${PROJECT_NAME} ${SOURCES_LIST})

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-system)
target_link_libraries(${PROJECT_NAME} boost_unit_test_framework)

target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_FILES_PATH}/SFML/include")
