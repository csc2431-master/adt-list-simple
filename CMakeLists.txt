cmake_minimum_required(VERSION 3.10)
project(adt_list_simple)

set(CMAKE_CXX_STANDARD 14)

add_executable(list fsarray.cpp fsarray.h integer.h integer.cpp
        linkedlist.h linkedlist.cpp list.h list.cpp object.h object.cpp person.h person.cpp
        lecture-code/lecture-code.cpp)