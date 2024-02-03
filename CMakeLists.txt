cmake_minimum_required(VERSION 3.10)
project(MatrixMindsArcade)

set(SOURCE_DIR "src")

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

set(INCLUDE_DIRS
    lib/matrix/include
    include/
)

set(LIBRARY_DIR
    lib/matrix/lib
)

include_directories(${INCLUDE_DIRS})
add_executable(matrix_minds ${SOURCES})

link_directories(${LIBRARY_DIR})

find_package(TBB REQUIRED)
target_link_libraries(matrix_minds PRIVATE
   ${TBB_IMPORTED_TARGETS} 
    -L./lib/matrix/lib
    -lrt
    -lm
    -lrgbmatrix
    -lpthread
    -lopencv_core
)

target_compile_features(matrix_minds PRIVATE cxx_std_20)

add_custom_target(run
    COMMAND ./matrix_minds    
    DEPENDS matrix_minds    
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

