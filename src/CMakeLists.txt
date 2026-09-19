set(SOURCES
    render/renderer.cpp

    render/opengl/program.cpp
    render/opengl/renderer.cpp

    window/window.cpp

    engine.cpp
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
