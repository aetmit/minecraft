cmake_minimum_required(VERSION 4.2)

project(minecraft LANGUAGES CXX)

# C++ 26 Standard enforced
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES)

add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES})

if (APPLE OR LINUX)  # Apple or Linux platform

    find_program(HOMEBREW brew)  # Get homebrew

    if (HOMEBREW)  # Homebrew
        # Get homebrew prefix
        execute_process(
            COMMAND ${HOMEBREW} --prefix
            OUTPUT_VARIABLE HOMEBREW_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )

        # Include homebrew /include directory
        target_include_directories(${PROJECT_NAME} PRIVATE
            "${HOMEBREW_PREFIX}/include"
            ${CMAKE_CURRENT_SOURCE_DIR}/include
        )
    endif()
endif()

find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    "-framework OpenGL"
)
