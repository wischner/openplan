add_executable(openplan main.cpp)

target_link_libraries(openplan PRIVATE openplan_lib)
target_include_directories(openplan PRIVATE ${CMAKE_SOURCE_DIR}/include)
