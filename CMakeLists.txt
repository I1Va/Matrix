
cmake_minimum_required(VERSION 3.10)
project(Matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 REQUIRED)

add_executable(Matrix main.cpp)
target_include_directories(Matrix PUBLIC ${CMAKE_SOURCE_DIR}/inc )
target_link_libraries(Matrix Eigen3::Eigen)

add_subdirectory(tests)