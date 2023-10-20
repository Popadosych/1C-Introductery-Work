cmake_minimum_required(VERSION 3.16)
project(1C_Introductery_Work)

set(CMAKE_CXX_STANDARD 17)

add_executable(1C_Introductery_Work
        main.cpp
        StringSimilarityCalculator.hpp
        StringSimilarityCalculator.cpp)

add_custom_target(run_my_program COMMAND main.cpp arg1 arg2 arg3)
