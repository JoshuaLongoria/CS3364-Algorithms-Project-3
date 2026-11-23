cmake_minimum_required(VERSION 3.10)
project(CS3364_Algorithms_Project_3 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic -O2")

add_executable(routes routes.c)

add_executable(test_routes test_routes.c routes.c)
target_compile_definitions(test_routes PRIVATE UNDEBUG)

# Optional sanitizer target
add_executable(test_routes_san test_routes.c routes.c)
target_compile_options(test_routes_san PRIVATE -g -fsanitize=address,undefined)
target_link_options(test_routes_san PRIVATE -fsanitize=address,undefined)
target_compile_definitions(test_routes_san PRIVATE UNDEBUG)