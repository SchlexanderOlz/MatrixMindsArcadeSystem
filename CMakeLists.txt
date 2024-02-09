cmake_minimum_required(VERSION 3.10)
include(FetchContent)
project(MatrixMindsArcade)

set(SOURCE_DIR "src")
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

set(INCLUDE_DIRS
    lib/matrix/include
    include/
)

FetchContent_Declare(rgbmatrix GIT_REPOSITORY https://github.com/hzeller/rpi-rgb-led-matrix
GIT_TAG a3eea997a9254b83ab2de97ae80d83588f696387)

FetchContent_Declare(pugixml GIT_REPOSITORY https://github.com/zeux/pugixml
GIT_TAG b2b466403084667c90a0f0cc4e960405cfc8117a)

FetchContent_MakeAvailable(rgbmatrix)
FetchContent_MakeAvailable(pugixml)


add_executable(matrix_minds ${SOURCES})

include_directories(${rgbmatrix_SOURCE_DIR}/include)
include_directories(${pugixml_SOURCE_DIR}/src)
include_directories(${INCLUDE_DIRS})

target_link_libraries(matrix_minds PRIVATE
   ${RGBMATRIX_LIBRARIES}
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
