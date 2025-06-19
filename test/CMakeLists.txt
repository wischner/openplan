include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SRC *.cpp)

add_executable(openplan_tests ${TEST_SRC})
target_include_directories(openplan_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(openplan_tests PRIVATE openplan_lib gtest_main)

add_test(NAME openplan_tests COMMAND openplan_tests)
