file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS *.cpp)

add_library(openplan STATIC ${LIB_SRC})

target_include_directories(openplan
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(openplan
  PUBLIC nlohmann_json::nlohmann_json
)
