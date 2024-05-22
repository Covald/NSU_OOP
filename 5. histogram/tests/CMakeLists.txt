file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES true *.hpp *.cpp)

set(SOURCES ${TEST_SOURCES})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${CMAKE_PROJECT_NAME}_test ${TEST_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME}_test gtest_main)
target_link_libraries(${CMAKE_PROJECT_NAME}_test ${CMAKE_PROJECT_NAME}_lib)
add_test(NAME ${CMAKE_PROJECT_NAME}_test COMMAND ${CMAKE_PROJECT_NAME}_test)

