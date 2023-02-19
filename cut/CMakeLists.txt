cmake_minimum_required(VERSION 3.22)

project (cut)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(main main.cpp)
add_executable(test cut_test.cpp)

add_library(libbitmap libbitmap.cpp)
add_library(mod bmpmod.cpp)
add_library(bmp bmp.cpp)

target_link_libraries(bmp libbitmap)

target_link_libraries(mod bmp)


target_link_libraries(main libbitmap)
target_link_libraries(main bmp)
target_link_libraries(main mod)

target_link_libraries(test gtest_main)
target_link_libraries(test libbitmap)
target_link_libraries(test bmp)
target_link_libraries(test mod)

set_source_files_properties(main.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
#set_source_files_properties(libbitmap.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(bmpmod.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(bmp.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(cut_test.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
