cmake_minimum_required(VERSION 3.14)
project(event-project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(event_lib
    src/shared/Event.cpp
    src/shared/Concert.cpp
    src/shared/Play.cpp
    src/shared/Screening.cpp
    src/shared/Room.cpp
)
target_include_directories(event_lib PUBLIC includes)

if(EXISTS ${CMAKE_SOURCE_DIR}/src/main.cpp)
    add_executable(planner src/main.cpp)
    target_link_libraries(planner PRIVATE event_lib)
endif()

enable_testing()

find_package(GTest REQUIRED)

add_executable(tests
    tests/test_room.cpp
    tests/test_concert.cpp
    tests/test_play.cpp
    tests/test_screening.cpp
)

target_link_libraries(tests
    PRIVATE
    event_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)