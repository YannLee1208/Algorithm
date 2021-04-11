cmake_minimum_required(VERSION 3.17)
project(Sort)

set(CMAKE_CXX_STANDARD 14)

add_executable(Sort main.cpp MergeSort.cpp BubbleSort.cpp Sort.h InsertSort.cpp)