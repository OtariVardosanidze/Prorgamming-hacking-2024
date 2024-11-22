if (WIN32)
    set(SOURCES
        command_handlers/process_win.cpp
    )
endif()

add_library(inject_lib 
    command_handlers/process_handler.h 
    ${SOURCES}
)

add_executable(inject
    main.cpp
)

set_target_properties(inject PROPERTIES CXX_STANDARD 17)

target_link_libraries(inject PUBLIC messages PUBLIC threading PUBLIC inject_lib)
target_include_directories(inject PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(inject PUBLIC core)