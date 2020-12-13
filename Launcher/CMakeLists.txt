cmake_minimum_required(
    VERSION 3.10.2
)
project(
    launcher
    VERSION 0.0.1
)

# TODO: Probably just move to Makefiles for MSYS2 based buils, doable
# in CI without much trouble.
# TODO: Fix 32/64 bit targeted builds. Possible with ninja?
# x86_64-w64-mingw32-g++ -municode -mwindows -static -static-libgcc -static-libstdc++ ../launcher.cc -o launcher64
# i686-w64-mingw32-g++ -municode -mwindows -static -static-libgcc -static-libstdc++ ../launcher.cc -o launcher32


# mingw-w64-x86_64-{boost, protobuf, protobuf-c}
# mingw-w64-i686-{...}
# protobuf-devel cmake ninja

set(CMAKE_MODULE_PATH "cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++2a -municode -mwindows")
# TODO: Fix cmake/msys2 so this isn't necessary.
set(CMAKE_CXX_COMPILER "/mingw64/bin/x86_64-w64-mingw32-g++")

find_package(
    Boost REQUIRED
    COMPONENTS iostreams
)
include_directories(${Boost_INCLUDE_DIRS})

find_package(
    Protobuf REQUIRED
)
include_directories(${Protobuf_INCLUDE_DIRS})
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS service.proto)

set_source_files_properties(
    launcher.cc PROPERTIES
    LANGUAGE CXX
)

add_executable(launcher launcher.cc ${PROTO_SRCS})
target_include_directories(
    "${PROJECT_NAME}"
    PUBLIC "${PROJECT_BINARY_DIR}"
)
target_link_libraries(
    "${PROJECT_NAME}"
    ${Boost_LIBRARIES}
    # TODO: Fix the below, finds /usr/lib... instead of right one.
    #${Protobuf_LIBRARIES}
    /mingw64/lib/libprotobuf.dll.a
)
target_link_options(
    "${PROJECT_NAME}" PRIVATE
    -static -static-libgcc -static-libstdc++
    -Wl,--enable-stdcall-fixup -Wl,--kill-at
)