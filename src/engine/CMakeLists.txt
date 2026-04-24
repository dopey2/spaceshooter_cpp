add_library(engine STATIC
    application.cpp
    scene.cpp
    scene_manager.cpp
    sprite.cpp
    sprite_animation.cpp
    world_object.cpp
    text.cpp
    assets_loader.cpp
    mouse_keyboard.cpp
    logger.cpp
)

target_link_libraries(engine PUBLIC
    SDL3::SDL3
    SDL3_ttf::SDL3_ttf
)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_compile_options(engine PRIVATE
    -Wall -Wextra -Wpedantic
    -Wshadow -Wconversion -Wsign-conversion
    -Wold-style-cast -Wnull-dereference
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(engine PRIVATE -fsanitize=address,undefined)
    target_link_options(engine PRIVATE -fsanitize=address,undefined)
endif()
