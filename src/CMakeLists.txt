set(SOURCES
    core/logger.cpp

    input/input.cpp

    render/renderer.cpp

    render/opengl/program.cpp
    render/opengl/renderer.cpp
    render/opengl/vertex_buffer.cpp

    window/window.cpp

    clock.cpp
    engine.cpp
    application.cpp
)

set(HEADERS ${CMAKE_SOURCE_DIR}/include)

add_library(
    core STATIC
    ${SOURCES}
)

target_include_directories(
    core PUBLIC
    ${HEADERS}
)

target_link_libraries(
    core PUBLIC
    glfw
    glad
    OpenGL::GL
)
