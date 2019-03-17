cmake_minimum_required(VERSION 2.8) 

set(PROJECT_NAME "game")
set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../source-files)
set(LIB_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib-files)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCES_LIST "${SOURCE_FILES_PATH}/main.cpp")
set(LIB "-L ${LIB_FILES_PATH}/SFML/lib -l sfml-graphics -l sfml-window -l sfml-system")

add_executable(${PROJECT_NAME} ${SOURCES_LIST})

target_link_libraries(${PROJECT_NAME} ${LIB})
target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_FILES_PATH}/SFML/include")