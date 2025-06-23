file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS *.cpp)

add_library(openplan STATIC ${LIB_SRC})

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)

target_include_directories(openplan
  PUBLIC ${CMAKE_SOURCE_DIR}/include
  PRIVATE ${CAIRO_INCLUDE_DIRS}
)

target_link_libraries(openplan
  PUBLIC nlohmann_json::nlohmann_json
  PRIVATE ${CAIRO_LIBRARIES}
)