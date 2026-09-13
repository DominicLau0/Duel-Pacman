cmake_minimum_required(VERSION 3.20)
project(Dual-Pacman LANGUAGES CXX C)

# State c++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

# Fetch raylib and enet from github
include(FetchContent)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Skip compiling sample games
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        6.0
)

FetchContent_Declare(
    enet
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG        master
)

# Download and populate both libraries
FetchContent_MakeAvailable(raylib enet)

# Ensure ENet exposes its header directory transitively to targets that link it
if(TARGET enet)
    target_include_directories(enet INTERFACE "${enet_SOURCE_DIR}/include")
endif()

file(GLOB CLIENT_SRCS CONFIGURE_DEPENDS "src/client/*.cc")
file(GLOB SERVER_SRCS CONFIGURE_DEPENDS "src/server/*.cc")

set(SHARED_SRCS
    src/shared/serialization.cc
    src/shared/deserialization.cc
)

if(WIN32)
    set(PLATFORM_LIBS ws2_32 winmm)
else()
    set(PLATFORM_LIBS pthread)
endif()

add_executable(client ${CLIENT_SRCS} ${SHARED_SRCS})

target_include_directories(client PRIVATE
    include
    src/shared
    src/client
)

target_link_libraries(client PRIVATE
    raylib
    enet
    ${PLATFORM_LIBS}
)

add_executable(server ${SERVER_SRCS} ${SHARED_SRCS})

target_include_directories(server PRIVATE
    include
    src/shared
    src/server
)

# The server typically does not need raylib (windowing/graphics/audio)
target_link_libraries(server PRIVATE
    enet
    ${PLATFORM_LIBS}
)