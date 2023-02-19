cmake_minimum_required (VERSION 3.22)
set (CMAKE_CXX_STANDARD 11)

project (whowhere)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(place place.cpp)

add_library(user user.cpp)
target_link_libraries(user place)

add_library(io io.cpp)
target_link_libraries(io place)
target_link_libraries(io user)

add_library(data database.cpp)
target_link_libraries(data place)
target_link_libraries(data user)
target_link_libraries(data io)


add_executable(main main.cpp)
target_link_libraries(main place)
target_link_libraries(main user)
target_link_libraries(main io)
target_link_libraries(main data)

add_executable(test test.cpp)
target_link_libraries(test place)
target_link_libraries(test user)
target_link_libraries(test io)
target_link_libraries(test gtest_main)
target_link_libraries(test data)
