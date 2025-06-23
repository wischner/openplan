add_executable(opview main.cpp)

target_link_libraries(opview PRIVATE openplan)
target_include_directories(opview PRIVATE ${CMAKE_SOURCE_DIR}/include)
