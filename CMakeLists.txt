#note: experimental
#      currently only used for generating `compile_commands.json` for clangd
#      to build this project, it's suggested to use `makefile` instead

cmake_minimum_required(VERSION 3.7)
project(speederv2)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    main.cpp
    log.cpp
    common.cpp
    lib/fec.cpp
    lib/rs.cpp
    packet.cpp
    delay_manager.cpp
    fd_manager.cpp
    connection.cpp
    fec_manager.cpp
    misc.cpp
    tunnel_client.cpp
    tunnel_server.cpp
    my_ev.cpp
    lib/Crc32.cpp
)

set(COMMON_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wno-unused-variable
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -O3
)

add_executable(speederv2 ${SOURCE_FILES})
target_compile_options(speederv2 PRIVATE ${COMMON_COMPILE_OPTIONS})

target_include_directories(speederv2 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/libev
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(speederv2 PRIVATE rt pthread)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
            target_compile_options(speederv2 PRIVATE -fsanitize=address,undefined)
            target_link_options(speederv2 PRIVATE -fsanitize=address,undefined)
        endif()
    endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(speederv2 PRIVATE ws2_32 pthread)
    target_compile_options(speederv2 PRIVATE
        -Wno-narrowing
        -Wno-sign-compare
        -Wno-type-limits
    )
    target_compile_definitions(speederv2 PRIVATE
        WIN32_LEAN_AND_MEAN
        _WIN32_WINNT=0x0601
        NOMINMAX
        INVALID_SOCKET=SOCKET\(-1\)
        SOCKET_ERROR=-1
    )
endif()

if(CMAKE_CROSSCOMPILING)
    set_target_properties(speederv2 PROPERTIES
        LINK_SEARCH_START_STATIC ON
        LINK_SEARCH_END_STATIC ON
    )
endif()