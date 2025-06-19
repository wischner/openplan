cmake_minimum_required(VERSION 3.10)
project(openplan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

include(FetchContent)

# Fetch nlohmann_json with timestamp option to avoid warnings
FetchContent_Declare(
  nlohmann_json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
  DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(nlohmann_json)

# Find and require Cairo
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)

# Expose variables to subdirectories
set(CAIRO_INCLUDE_DIRS ${CAIRO_INCLUDE_DIRS} CACHE INTERNAL "")
set(CAIRO_LIBRARIES ${CAIRO_LIBRARIES} CACHE INTERNAL "")
set(CAIRO_CFLAGS_OTHER ${CAIRO_CFLAGS_OTHER} CACHE INTERNAL "")

enable_testing()

# Project subdirectories
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)
