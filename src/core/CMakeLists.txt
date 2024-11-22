add_subdirectory(messages)
add_subdirectory(network)
add_subdirectory(threading)

add_library(core core.h core.cpp)

target_link_libraries(
    core 
    PUBLIC messages
    PUBLIC network
    PUBLIC threading
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_LIST_DIR})