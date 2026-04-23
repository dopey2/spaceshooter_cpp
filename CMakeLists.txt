cmake_minimum_required(VERSION 3.10)
project(Spaceship)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/engine/application.cpp
        src/engine/scene.cpp
        src/engine/scene_manager.cpp
        src/engine/sprite.cpp
        src/engine/sprite_animation.cpp
        src/engine/world_object.cpp
        src/engine/text.cpp
        src/engine/assets_loader.cpp
        src/engine/mouse_keyboard.cpp
        src/engine/logger.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall -Wextra -Wpedantic
    -Wshadow -Wconversion -Wsign-conversion
    -Wold-style-cast -Wnull-dereference
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address,undefined)
endif()
