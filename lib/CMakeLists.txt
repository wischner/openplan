file(GLOB_RECURSE LIB_SRC CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/openplan/*.cpp)

add_library(openplan_lib STATIC ${LIB_SRC})

target_include_directories(openplan_lib
  PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(openplan_lib
  PUBLIC nlohmann_json::nlohmann_json
)
