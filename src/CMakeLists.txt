set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND SOURCES
    ${DIR}/main.cpp
    ${DIR}/engine.cpp
)

add_subdirectory(window)
add_subdirectory(render)

set(SOURCES ${SOURCES} PARENT_SCOPE)