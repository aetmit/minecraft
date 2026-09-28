set(SOURCES
    core/logger.cpp

    input/input.cpp

    render/renderer.cpp
    render/mesh.cpp
    render/vertex.cpp

    render/opengl/shader.cpp
    render/opengl/renderer.cpp
    render/opengl/vertex_array.cpp
    render/opengl/vertex_buffer.cpp
    render/opengl/index_buffer.cpp 
    render/opengl/texture.cpp
    render/opengl/mesh.cpp

    math/vec2.cpp
    math/vec3.cpp

    camera/camera.cpp

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
    stbi
    glfw
    glad
    OpenGL::GL
)
