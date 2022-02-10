cmake_minimum_required(VERSION 3.2)
project(async)

set(CMAKE_CXX_STANDARD 17)

add_executable(async_cli main.cpp)

target_link_libraries(async_cli async)

if (MSVC)
    target_compile_options(async_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(async_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS async_cli RUNTIME DESTINATION bin)