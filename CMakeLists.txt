cmake_minimum_required(VERSION 3.10)
project(Spaceship)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/libs/SDL3-3.2.8/include)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/engine/application.cpp
        src/engine/scene.cpp
        src/engine/sprite.cpp
        src/engine/world_object.cpp
        src/engine/texture.cpp
)

# Link against SDL3
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/libs/SDL3-3.2.8/lib/libSDL3.dll.a)

# Copy SDL3.dll to the output directory post-build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/SDL3-3.2.8/bin/SDL3.dll"
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)