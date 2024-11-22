include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.15.2
)

FetchContent_MakeAvailable(googletest)

file(GLOB INJECT_TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/inject/*.cpp)
add_executable(inject_tests ${INJECT_TEST_SOURCES})
target_link_libraries(inject_tests GTest::gtest_main)

file(GLOB CLIENT_TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/client/*.cpp)
add_executable(client_tests ${CLIENT_TEST_SOURCES})
target_link_libraries(client_tests GTest::gtest_main)

file(GLOB CORE_TEST_SOURCES ${PROJECT_SOURCE_DIR}/test/core/*.cpp)
add_executable(core_tests ${CORE_TEST_SOURCES})
target_link_libraries(core_tests GTest::gtest_main core)

include(GoogleTest)
gtest_discover_tests(inject_tests)
gtest_discover_tests(client_tests)
gtest_discover_tests(core_tests)

