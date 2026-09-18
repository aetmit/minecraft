cmake_minimum_required(VERSION 4.2)

project(minecraft LANGUAGES C CXX)

# Set C++ standard 23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROGRAM_NAME minecraft)

# Link GLAD Library as a static library
add_library(glad STATIC "deps/glad/src/glad.c")
target_include_directories(glad PUBLIC "deps/glad/include")

# Linux: GLAD requires dynamic loader library to fetch OpenGL pointers
if(NOT WIN32 AND NOT APPLE)
    target_link_libraries(glad PRIVATE ${CMAKE_DL_LIBS})
endif()

if (APPLE OR LINUX)  # Apple or Linux platform

    find_program(HOMEBREW brew)  # Get homebrew

    if (HOMEBREW)  # Homebrew
        # Get homebrew prefix
        execute_process(
            COMMAND ${HOMEBREW} --prefix
            OUTPUT_VARIABLE HOMEBREW_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
        )

        if (HOMEBREW_PREFIX)
            list(APPEND CMAKE_PREFIX_PATH "${HOMEBREW_PREFIX}")
        endif()
    endif()
endif()

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(${CMAKE_SOURCE_DIR}/src)

add_executable(${PROGRAM_NAME} src/main.cpp "deps/glad/src/glad.c")

target_link_libraries(${PROGRAM_NAME} PRIVATE
    glfw
    glad
    OpenGL::GL

    core
)
