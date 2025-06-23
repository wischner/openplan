include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Gather test sources
file(GLOB TEST_SRC *.cpp)
add_executable(optests ${TEST_SRC})

# Include and link
target_include_directories(optests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(optests PRIVATE openplan gtest_main)

# Copy all data files (*.json) from test/data to build/data
file(GLOB TEST_DATA_FILES "${CMAKE_CURRENT_SOURCE_DIR}/data/*.json")

foreach(DATA_FILE ${TEST_DATA_FILES})
  get_filename_component(FILE_NAME ${DATA_FILE} NAME)
  configure_file(${DATA_FILE} ${CMAKE_CURRENT_BINARY_DIR}/data/${FILE_NAME} COPYONLY)
endforeach()

# Define macro with test data dir path
target_compile_definitions(optests PRIVATE
    TEST_DATA_DIR="${CMAKE_CURRENT_BINARY_DIR}/data"
)

add_test(NAME optests COMMAND optests)
