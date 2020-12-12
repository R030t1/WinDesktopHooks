cmake_minimum_required(
    VERSION 3.10.2
)
project(
    injectable
    VERSION 0.0.1
)

# TODO: Fix 32/64 bit targeted builds.
# The static compilation options fix MinGW-compiled 32 bit libs.
# 64 bit works fine without it.
# x86_64-w64-mingw32-g++ -municode -shared -static -static-libgcc -static-libstdc++ -Wl,--enable-stdcall-fixup -Wl,--kill-at injectable.cc -o libinjectable64.dll
# i686-w64-mingw32-g++ -municode -shared -static -static-libgcc -static-libstdc++ -Wl,--enable-stdcall-fixup -Wl,--kill-at injectable.cc -o libinjectable32.dll

set(CMAKE_MODULE_PATH "cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a -municode")

# TODO: Fix cmake/msys2 so this isn't necessary.
set(CMAKE_CXX_COMPILER "/mingw64/bin/x86_64-w64-mingw32-g++")

find_package(
    Protobuf REQUIRED
)
include_directories(${Protobuf_INCLUDE_DIRS})
#protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS records.proto)

# TODO: Wildcard .cc files.
set_source_files_properties(
    injectable.cc PROPERTIES
    LANGUAGE CXX
)

add_library("${PROJECT_NAME}" SHARED injectable.cc ${PROTO_SRCS})
target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    "${PROJECT_NAME}"
    ${Protobuf_LIBRARIES}
)
target_link_options(
    "${PROJECT_NAME}" PRIVATE
    -static -static-libgcc -static-libstdc++
    -Wl,--enable-stdcall-fixup -Wl,--kill-at
)