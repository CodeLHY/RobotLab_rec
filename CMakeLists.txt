cmake_minimum_required(VERSION 3.0.0)
project(chasing_first VERSION 0.1.0)

include(CTest)
enable_testing()

add_library(chasing_first chasing_first.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})


aux_source_directory(. DIR_SRCS)
find_package(OpenCV)
include_directories(${OpenCV_INCLUDES})
add_executable(first ${DIR_SRCS})
target_link_libraries(first ${OpenCV_LIBS})


include(CPack)
