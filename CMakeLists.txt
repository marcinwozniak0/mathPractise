cmake_minimum_required(VERSION 3.10)

project(MathPractise)

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

include(External_GTest.cmake)

add_executable(my_project "main.cpp")

set(TEST_BINARY_FILES "ExercisesTest.cpp")

add_executable(my_project_UT ${TEST_BINARY_FILES})
target_link_libraries(my_project_UT ${GTEST_MAIN_LIBRARY}
				    ${GTEST_LIBRARY}
				    ${GMOCK_MAIN_LIBRARY}
				    ${GMOCK_LIBRARY})

