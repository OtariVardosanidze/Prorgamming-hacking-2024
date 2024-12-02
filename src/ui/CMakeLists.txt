                                                                               
add_executable(ui main.cpp machine_ui.cpp machine_ui.h)

target_include_directories(ui PUBLIC ../../third_party/elements/lib/include PUBLIC ../../build/_deps/cycfi_infra-src/include PUBLIC ../../build/_deps/asio-src/asio/include)

target_link_libraries(ui PUBLIC elements)