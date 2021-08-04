cmake_minimum_required(VERSION 3.0)

project(finnesse LANGUAGES C)

add_executable(finnesse src/main.c src/cpu.c src/memory.c)

install(TARGETS finnesse RUNTIME DESTINATION bin)
