cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(MatrixGenerator matrix_generator.cpp)
target_include_directories(MatrixGenerator 
    PRIVATE ${CMAKE_SOURCE_DIR}/inc
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/inc    
)

add_executable(UnitTests unit_tests.cpp)
target_include_directories(UnitTests 
    PRIVATE ${CMAKE_SOURCE_DIR}/inc
    PRIVATE ${CMAKE_SOURCE_DIR}/tests/inc    
)

target_link_libraries(UnitTests PRIVATE
   gtest
   gtest_main
)
target_compile_options(UnitTests PRIVATE -fsanitize=address -fno-omit-frame-pointer)
target_link_options(UnitTests PRIVATE -fsanitize=address)