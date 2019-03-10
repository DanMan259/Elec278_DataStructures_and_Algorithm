cmake_minimum_required(VERSION 3.12)
project(lab3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(lab3
        bst.c
        bst.h
        main.c
        makefile
        mytree)
