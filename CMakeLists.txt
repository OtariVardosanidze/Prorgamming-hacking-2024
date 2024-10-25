cmake_minimum_required(VERSION 3.5)

project(rconsole)

add_subdirectory(src/inject)


set(ELEMENTS_BUILD_EXAMPLES OFF)
set(PKG_CONFIG_EXECUTABLE vcpkg.exe)
add_subdirectory(third_party/elements)
