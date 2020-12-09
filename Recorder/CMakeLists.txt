cmake_minimum_required(
    VERSION 3.10.2
)
project(
    recorder
    VERSION 0.0.1
)

#set_source_file_properties(
#    recorder.cc PROPERTIES
#    LANGUAGE "CXX"
#)

set(CMAKE_MODULE_PATH "cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a -municode -mwindows")

find_package(
    Boost REQUIRED
    COMPONENTS iostreams
)
include_directories(${Boost_INCLUDE_DIRS})

find_package(
    Protobuf REQUIRED
)
include_directories(${Protobuf_INCLUDE_DIRS})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS records.proto)

add_executable(recorder recorder.cc ${PROTO_SRCS})
target_include_directories(
    recorder
    PUBLIC "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    recorder
    Boost::iostreams
    ${Protobuf_LIBRARIES}
)