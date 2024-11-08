cmake_minimum_required(VERSION 3.5)

project(rconsole)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src/inject)


set(ELEMENTS_BUILD_EXAMPLES OFF)
add_subdirectory(third_party/elements)
add_subdirectory(src/ui)