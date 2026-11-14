cmake_minimum_required(VERSION 3.14)
project(event-project CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(event_lib
    src/shared/Admin.cpp
    src/shared/Booking.cpp
    src/shared/Persistence.cpp
    src/logger/Logger.cpp
    src/shared/Concert.cpp 
    src/shared/Program.cpp
    src/shared/Play.cpp
    src/shared/Screening.cpp
    src/shared/Menu.cpp
    src/shared/Event.cpp
    src/Main.cpp
    src/shared/Room.cpp
    src/shared/Schedule.cpp
    
)
target_include_directories(event_lib PUBLIC includes includes/shared includes/logger)

if(EXISTS ${CMAKE_SOURCE_DIR}/src/main.cpp)
    add_executable(planner src/main.cpp)
    target_link_libraries(planner PRIVATE event_lib)
endif()


find_package(GTest QUIET)

if(GTest_FOUND)
    enable_testing()
    add_executable(tests
    tests/test_room.cpp
    tests/test_concert.cpp
    tests/test_play.cpp
    tests/test_screening.cpp
    tests/test_schedule.cpp
    tests/test_program.cpp
    tests/test_Admin.cpp
    tests/test_Booking.cpp
    tests/test_Logger.cpp
    
)

target_link_libraries(tests
    PRIVATE
    event_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)

else()
    message(STATUS "GoogleTest not found: unit tests are not built")

endif()

