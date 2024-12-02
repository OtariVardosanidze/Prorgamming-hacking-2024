                                                                               
add_executable(ui
  main.cpp
  machine_ui.cpp
  machine_ui.h
  machine_list_ui.cpp
  machine_list_ui.h
  workspace_ui.cpp
  workspace_ui.h
)

target_include_directories(ui PUBLIC ../../third_party/elements/lib/include PUBLIC ../../build/_deps/cycfi_infra-src/include PUBLIC ../../build/_deps/asio-src/asio/include)

target_link_libraries(ui PUBLIC elements)