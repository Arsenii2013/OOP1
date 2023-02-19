cmake_minimum_required(VERSION 3.22)

project (edge)

add_library(edge edge.cpp)
add_library(point point.cpp)
add_library(dsu dsu.cpp)
add_library(graph graph.cpp)
add_library(io io.cpp)
add_executable(main main.cpp)

target_link_libraries(main edge)
target_link_libraries(main point)
target_link_libraries(main dsu)
target_link_libraries(main graph)
target_link_libraries(main io)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test tree_test.cpp)
target_link_libraries(test gtest_main)
target_link_libraries(test edge)
target_link_libraries(test point)
target_link_libraries(test dsu)
target_link_libraries(test graph)
target_link_libraries(test io)

target_link_libraries(graph dsu)
target_link_libraries(graph edge)
target_link_libraries(graph point)

target_link_libraries(io point)

add_test(NAME example_test COMMAND edge)

set_source_files_properties(main.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(edge.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(tree_test.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(dsu.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(graph.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(io.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")




