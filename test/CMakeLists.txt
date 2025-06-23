include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_SRC *.cpp)

add_executable(optests ${TEST_SRC})
target_include_directories(optests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(optests PRIVATE openplan gtest_main)

# Copy test data file to build dir
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/plan1.json
               ${CMAKE_CURRENT_BINARY_DIR}/data/plan1.json
               COPYONLY)

# Define path macro for locating test data at runtime
target_compile_definitions(optests PRIVATE
    TEST_DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data"
)

add_test(NAME optests COMMAND optests)
