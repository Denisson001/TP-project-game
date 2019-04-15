cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME "game")
project(${PROJECT_NAME})

set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../source_files)
set(LIB_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../lib_files)

link_directories(${LIB_FILES_PATH}/SFML/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2 -Wall")

add_executable(${PROJECT_NAME}  ${SOURCE_FILES_PATH}/main.cpp
				${SOURCE_FILES_PATH}/modules/game.cpp
				${SOURCE_FILES_PATH}/modules/geometry.cpp
				${SOURCE_FILES_PATH}/modules/enemy_units.cpp
				${SOURCE_FILES_PATH}/modules/hero_unit.cpp
				${SOURCE_FILES_PATH}/modules/window.cpp
				${SOURCE_FILES_PATH}/modules/units_factories.cpp
				${SOURCE_FILES_PATH}/modules/controller.cpp
				${SOURCE_FILES_PATH}/modules/bullet.cpp
				${SOURCE_FILES_PATH}/modules/game_proxy.cpp
				${SOURCE_FILES_PATH}/modules/enemy_super_attack_decorator.cpp
				${SOURCE_FILES_PATH}/modules/enemy_movement_decorator.cpp
				${SOURCE_FILES_PATH}/modules/units.cpp
				${SOURCE_FILES_PATH}/modules/enemy_unit_decorator.cpp
				${SOURCE_FILES_PATH}/modules/logging_module.cpp
				${SOURCE_FILES_PATH}/modules/enemy_units_booster.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-window)
target_link_libraries(${PROJECT_NAME} sfml-system)

target_include_directories(${PROJECT_NAME} PUBLIC "${LIB_FILES_PATH}/SFML/include")

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/modules/headers")
target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/settings")
