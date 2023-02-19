cmake_minimum_required(VERSION 3.22)

project (palindroms)

add_library(palindroms palindroms.cpp)
add_executable(main main.cpp)

target_link_libraries(main palindroms)

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

add_executable(test palindroms_test.cpp)
target_link_libraries(test gtest_main)
target_link_libraries(test palindroms)
add_test(NAME example_test COMMAND palindroms)
#target_compile_options(main PRIVATE -Wall)
#target_compile_features(main cxx_std_17)
#set_source_files_properties(main.cpp PROPERTIES COMPILE_OPTIONS "-Wno-unused-parameter;-Wno-missing-field-initializer")
set_source_files_properties(main.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(palindroms_test.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")
set_source_files_properties(palindroms.cpp PROPERTIES COMPILE_OPTIONS "-Wall;-Wextra;-D_GLIBCXX_DEBUG;-D_GLIBCXX_DEBUG_PEDANTIC")