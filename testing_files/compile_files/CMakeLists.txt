cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME "tests")
project(${PROJECT_NAME})

set(TESTS_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../source_files)
set(LIB_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../lib_files)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

add_definitions(-DTESTING_MODE)

link_directories(${LIB_FILES_PATH}/SFML/lib)

add_executable(${PROJECT_NAME}  ${TESTS_FILES_PATH}/tests/main.cpp

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
								${SOURCE_FILES_PATH}/modules/enemy_units_booster.cpp
								${SOURCE_FILES_PATH}/modules/hero_unit_attack_module.cpp
								${SOURCE_FILES_PATH}/modules/text_helper.cpp

								${TESTS_FILES_PATH}/tests/geometric_module_tests.cpp
								${TESTS_FILES_PATH}/tests/bullets_module_tests.cpp
								${TESTS_FILES_PATH}/tests/game_proxy_tests.cpp
								${TESTS_FILES_PATH}/tests/enemy_units_booster_tests.cpp
								${TESTS_FILES_PATH}/tests/units_factories_tests.cpp
								${TESTS_FILES_PATH}/tests/hero_unit_attack_module_tests.cpp
								${TESTS_FILES_PATH}/tests/enemy_units_tests.cpp
								${TESTS_FILES_PATH}/tests/game_module_tests.cpp
								${TESTS_FILES_PATH}/tests/hero_unit_tests.cpp
								${TESTS_FILES_PATH}/tests/enemy_units_decorators_tests.cpp
								${TESTS_FILES_PATH}/tests/text_helper_tests.cpp
								${TESTS_FILES_PATH}/tests/units_tests.cpp
								${TESTS_FILES_PATH}/tests/logging_module_tests.cpp

								${TESTS_FILES_PATH}/modules/testing_module.cpp
								${TESTS_FILES_PATH}/modules/fake_controller.cpp)

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

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/modules/headers")
target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/settings")

target_include_directories(${PROJECT_NAME} PUBLIC "${TESTS_FILES_PATH}/modules/headers")
