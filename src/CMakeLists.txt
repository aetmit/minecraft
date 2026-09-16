set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

list(APPEND SOURCES
    ${DIR}/main.cpp
)

add_subdirectory(engine)

set(SOURCES ${SOURCES} PARENT_SCOPE)