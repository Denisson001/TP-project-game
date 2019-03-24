cmake_minimum_required(VERSION 2.8) 

set(PROJECT_NAME "tests")
set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../tests)
set(LIB_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../lib_files)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCES_LIST "${SOURCE_FILES_PATH}/tests.cpp")

message(${SOURCES_LIST})

link_directories(${LIB_FILES_PATH}/SFML/lib)

add_executable(${PROJECT_NAME} ${SOURCES_LIST})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost library")
	return()
else()
	target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-system)

target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_FILES_PATH}/SFML/include")

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../../source_files")
