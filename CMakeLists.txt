cmake_minimum_required(VERSION 3.16)
project(practica06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# AddressSanitizer (opcional / demostrativo)
option(ENABLE_ASAN "Habilitar AddressSanitizer (opcional/demostrativo)" OFF)
if(ENABLE_ASAN)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang" AND NOT WIN32)
        message(STATUS "AddressSanitizer (ASan) habilitado: -fsanitize=address -g")
        add_compile_options(-fsanitize=address -g -fno-omit-frame-pointer)
        add_link_options(-fsanitize=address)
    else()
        message(WARNING "AddressSanitizer omitido: no compatible o susceptible a problemas de enlazado en este entorno.")
    endif()
endif()

# SDL3
find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3 REQUIRED IMPORTED_TARGET sdl3)
    set(SDL3_TARGET PkgConfig::SDL3)
else()
    set(SDL3_TARGET SDL3::SDL3)
endif()

# SDL3_image
find_package(SDL3_image QUIET)
if(NOT SDL3_image_FOUND)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL3_IMAGE REQUIRED IMPORTED_TARGET sdl3-image)
    set(SDL3_IMAGE_TARGET PkgConfig::SDL3_IMAGE)
else()
    set(SDL3_IMAGE_TARGET SDL3_image::SDL3_image)
endif()

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Vector2.cpp
    src/GameObject.cpp
    src/Scene.cpp
    src/SceneManager.cpp
    src/ResourceManager.cpp
    src/TransformComponent.cpp
    src/RectRenderComponent.cpp
    src/SpriteComponent.cpp
    src/ColliderComponent.cpp
    src/CollisionManager.cpp
    src/ResourceDemoScene.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE include src)
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL3_TARGET} ${SDL3_IMAGE_TARGET})

# Copiar assets junto al ejecutable
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})