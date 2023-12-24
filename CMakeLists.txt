cmake_minimum_required(VERSION 3.10)
project(MatrixMindsArcade)

set(SOURCES
    src/main.cpp
)

set(INCLUDE_DIRS
    lib/matrix/include
)

set(LIBRARY_DIR
    lib/matrix/lib
)

include_directories(${INCLUDE_DIRS})
add_executable(matrix_minds ${SOURCES})

link_directories(${LIBRARY_DIR})

target_link_libraries(matrix_minds PRIVATE
    -L./lib/matrix/lib
    -lrt
    -lm
    -lrgbmatrix
    -lpthread
)

add_custom_target(run
    COMMAND ./matrix_minds    
    DEPENDS matrix_minds    
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
