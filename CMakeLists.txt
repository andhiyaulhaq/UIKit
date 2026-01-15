cmake_minimum_required(VERSION 3.16)
project(ui_kit LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =========================
# External dependencies
# =========================
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/../external)

# -------------------------
# GLFW
# -------------------------
add_subdirectory(${EXTERNAL_DIR}/glfw external_glfw)

# -------------------------
# GLAD
# -------------------------
add_library(glad
    ${EXTERNAL_DIR}/glad/src/gl.c
)

target_include_directories(glad PUBLIC
    ${EXTERNAL_DIR}/glad/include
)

# -------------------------
# ImGui
# -------------------------
add_library(imgui
    ${EXTERNAL_DIR}/imgui/imgui.cpp
    ${EXTERNAL_DIR}/imgui/imgui_draw.cpp
    ${EXTERNAL_DIR}/imgui/imgui_tables.cpp
    ${EXTERNAL_DIR}/imgui/imgui_widgets.cpp
    ${EXTERNAL_DIR}/imgui/backends/imgui_impl_glfw.cpp
    ${EXTERNAL_DIR}/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
    ${EXTERNAL_DIR}/imgui
    ${EXTERNAL_DIR}/imgui/backends
    ${EXTERNAL_DIR}/glfw/include
    ${EXTERNAL_DIR}/glad/include
)

target_link_libraries(imgui PUBLIC
    glfw
    glad
    opengl32
)

# =========================
# UI Kit library
# =========================
add_library(ui_kit
    include/ui/primitives/button.cpp
    include/ui/primitives/input.cpp
    include/ui/tokens/theme.cpp
    # later:
    # include/ui/patterns/toolbar.cpp
)

target_include_directories(ui_kit PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(ui_kit PUBLIC
    imgui
)

# =========================
# ASSET COPYING AUTOMATION
# =========================
# 1. Define where your assets live in the source code
set(ASSETS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/assets")

# 2. Define where they should go (into the build directory root)
set(ASSETS_DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}/assets")

# 3. Copy the folder automatically after ui_kit is built
add_custom_command(TARGET ui_kit POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_SOURCE_DIR}
    ${ASSETS_DEST_DIR}
    COMMENT "Copying assets to build directory..."
)

# =========================
# Examples
# =========================
add_subdirectory(examples)
