cmake_minimum_required(VERSION 3.5)

project(rconsole)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(protobuf_BUILD_TESTS OFF)
set(ABSL_PROPAGATE_CXX_STD ON)
add_subdirectory(third_party/protobuf EXCLUDE_FROM_ALL)

add_subdirectory(src/inject)

add_subdirectory(src/core/messages)

