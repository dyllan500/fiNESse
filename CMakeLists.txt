cmake_minimum_required(VERSION 3.0)
project(finnesse LANGUAGES C)
set(CMAKE_BUILD_TYPE DEBUG)

add_executable(finnesse src/main.c src/cpu.c src/memory.c src/cartridge.c src/ppu.c src/display.c)
INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} ${SDL2TTF_LIBRARIES})

install(TARGETS finnesse RUNTIME DESTINATION bin)
