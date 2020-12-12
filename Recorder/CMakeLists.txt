cmake_minimum_required(
    VERSION 3.10.2
)
project(
    recorder
    VERSION 0.0.1
)

# TODO: Fix 32/64 bit targeted builds. Possible with ninja?
# x86_64-w64-mingw32-g++ -municode -mwindows -static -static-libgcc -static-libstdc++ recorder.cc -o recorder64
# i686-w64-mingw32-g++ -municode -mwindows -static -static-libgcc -static-libstdc++ recorder.cc -o recorder32


# mingw-w64-x86_64-{boost, protobuf, protobuf-c}
# mingw-w64-i686-{...}
# protobuf-devel cmake ninja

set(CMAKE_MODULE_PATH "cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a -municode")

find_package(
    Boost REQUIRED
    COMPONENTS system program_options iostreams
)
include_directories(${Boost_INCLUDE_DIRS})

find_package(
    Protobuf REQUIRED
)
include_directories(${Protobuf_INCLUDE_DIRS})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS records.proto)

set_source_files_properties(
    recorder.cxx PROPERTIES
    LANGUAGE CXX
)

add_executable(recorder recorder.cc ${PROTO_SRCS})
target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    "${PROJECT_NAME}"
    ws2_32
    Boost::system
    Boost::program_options
    Boost::iostreams
    ${Protobuf_LIBRARIES}
)
target_link_options(
    "${PROJECT_NAME}" PRIVATE
    -static -static-libgcc -static-libstdc++
    -Wl,--enable-stdcall-fixup -Wl,--kill-at
)