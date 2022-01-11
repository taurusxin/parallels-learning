cmake_minimum_required(VERSION 3.21)
project(hello_omp)

find_package(OpenMP REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(hello_omp main.cpp)

if(OpenMP_CXX_FOUND)
    target_link_libraries(hello_omp PUBLIC OpenMP::OpenMP_CXX)
endif()