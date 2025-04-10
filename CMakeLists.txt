cmake_minimum_required(VERSION 3.10)
project(Spaceship)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/libs/SDL3-3.2.8/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/SDL_TTF-3.2.0/include)

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
        src/engine/keyboard.cpp
        src/engine/logger.cpp
        src/engine/view.cpp
)

# Link against SDL3
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/SDL3-3.2.8/lib/libSDL3.dll.a)

# Copy SDL3.dll to the output directory post-build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/SDL3-3.2.8/bin/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# Link against SDL_TTF
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/SDL_TTF-3.2.0/lib/libSDL3_ttf.dll.a)

# Copy SDL3.dll to the output directory post-build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/SDL_TTF-3.2.0/bin/SDL3_ttf.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)