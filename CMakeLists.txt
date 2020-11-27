cmake_minimum_required(VERSION 3.10)

project(ProjectEuler)

set(LIBRARY_OUTPUT_PATH build/)
set(BINARY_OUTPUT_PATH build/)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g3 -pthread -fconcepts")

include(External_GTest.cmake)

add_library(source_objects_lib OBJECT "NamesScore.cpp"
                                      "LargeSum.cpp")

add_executable(project_euler $<TARGET_OBJECTS:source_objects_lib>
                             "main.cpp")

set(TEST_BINARY_FILES $<TARGET_OBJECTS:source_objects_lib>
                      "NamesScoreTest.cpp"
                      "LargeSumTest.cpp")
add_executable(project_euler_ut ${TEST_BINARY_FILES})

target_link_libraries(project_euler_ut ${GTEST_MAIN_LIBRARY}
                                       ${GTEST_LIBRARY}
                                       ${GMOCK_MAIN_LIBRARY}
                                       ${GMOCK_LIBRARY})

# Valgrind
find_program(VALGRIND "valgrind")
if(VALGRIND)
target_link_libraries(project_euler_ut LINK_PUBLIC)
add_custom_target(valgrind COMMAND "${VALGRIND}" --tool=memcheck
                                                 --leak-check=yes
                                                 --show-reachable=yes
                                                 --num-callers=20
                                                 --track-fds=no
                                                 --track-origins=yes
                                                 --error-exitcode=1
                                                 $<TARGET_FILE:project_euler_ut>)
endif()
