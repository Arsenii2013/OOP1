cmake_minimum_required (VERSION 3.22)

project (esort)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg

add_executable(main main.cpp)

add_executable(test test.cpp)
target_link_libraries(test gtest_main)

add_library(merge merge.cpp)
target_link_libraries(main merge)
target_link_libraries(test merge)

add_library(io io.cpp)
target_link_libraries(main io)
target_link_libraries(test io)
target_link_libraries(merge io)

set_source_files_properties(main.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(merge.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(test.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(io.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")