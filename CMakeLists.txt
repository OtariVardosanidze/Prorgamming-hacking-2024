cmake_minimum_required(VERSION 3.5)

project(rconsole)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(protobuf_BUILD_TESTS OFF)
set(ABSL_PROPAGATE_CXX_STD ON)
set(gtest_force_shared_crt ON)
add_subdirectory(third_party/protobuf EXCLUDE_FROM_ALL)

add_subdirectory(src/inject)

add_subdirectory(src/core)

add_subdirectory(src/client)

add_subdirectory(test)