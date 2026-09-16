cmake_minimum_required(VERSION 4.2)

project(game)

set(SOURCES)

add_subdirectory(src)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE -std=c++26)

target_include_directories(${PROJECT_NAME} PRIVATE
    "/opt/homebrew/include"
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_package(glfw3 REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    "-framework OpenGL"
)