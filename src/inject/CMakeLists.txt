if (WIN32)
    set(SOURCES
        command_handlers/process_win.cpp
    )
endif()

add_executable(inject
    command_handlers/process_handler.h
    ${SOURCES}

)

set_target_properties(inject PROPERTIES CXX_STANDARD 17)

