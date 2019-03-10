cmake_minimum_required(VERSION 3.12)
project(lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab4
        avl.c
        avl.h
        avltrees
        main.c)
