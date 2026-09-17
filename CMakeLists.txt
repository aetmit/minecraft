cmake_minimum_required(VERSION 4.2)

project(minecraft LANGUAGES C CXX)

# C++ 23 Standard enforced
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES)

add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES} "deps/glad/src/glad.c")

target_include_directories(${PROJECT_NAME} PRIVATE
    "/opt/homebrew/include"
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

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

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
)