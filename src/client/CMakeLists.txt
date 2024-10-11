add_executable(client
    main.cpp
    ${SOURCES}
)

set_target_properties(client PROPERTIES CXX_STANDARD 17)

target_link_libraries(client PUBLIC messages)
target_include_directories(client PUBLIC ${CMAKE_CURRENT_BINARY_DIR})