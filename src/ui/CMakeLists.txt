                                                                               
add_executable(ui main.cpp)

target_include_directories(ui PUBLIC ../../third_party/elements/lib/include PUBLIC ../../build/_deps/cycfi_infra-src/include PUBLIC ../../build/_deps/asio-src/asio/include)

target_link_libraries(ui PUBLIC elements)