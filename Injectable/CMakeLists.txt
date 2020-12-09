cmake_minimum_required(
    VERSION 3.10.2
)
project(
    injectable
    VERSION 0.0.1
)

#set_source_file_properties(
#    recorder.cc PROPERTIES
#    LANGUAGE "CXX"
#)

set(CMAKE_MODULE_PATH "cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a -municode")

find_package(
    Protobuf REQUIRED
)
include_directories(${Protobuf_INCLUDE_DIRS})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS records.proto)

add_library(injectable SHARED
    injectable.cc ${PROTO_SRCS}
)
target_include_directories(
    injectable
    PUBLIC "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    injectable
    ${Protobuf_LIBRARIES}
)