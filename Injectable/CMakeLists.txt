cmake_minimum_required(
    VERSION 3.10.2
)
project(
    injectable
    VERSION 0.0.1
)

# TODO: Fix 32/64 bit targeted builds.
# x86_64-w64-mingw32-g++ -municode -shared injectable.cc -o libinjectable64.dll
# i686-w64-mingw32-g++ -municode -shared injectable.cc -o libinjectable32.dll

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