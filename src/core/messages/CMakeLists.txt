message(${CMAKE_BINARY_DIR})

include("${CMAKE_BINARY_DIR}/third_party/protobuf/cmake/protobuf/protobuf-generate.cmake")

add_library(messages test.proto)  # Тут вместо test.proto файлики с сообщениями
target_link_libraries(messages PUBLIC libprotobuf) # линкуем с протобафом
protobuf_generate(TARGET messages LANUAGE cpp)  # Запускаем генератор