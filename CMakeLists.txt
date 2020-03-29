cmake_minimum_required(VERSION 3.15)
project(unicode_to_re2c)

set(CMAKE_CXX_STANDARD 20)

include_directories(unilib/unilib)

add_executable(unicode_to_re2c
        unilib/unilib/unicode.cpp
        unilib/unilib/unicode.h
        unilib/unilib/uninorms.cpp
        unilib/unilib/uninorms.h
        unilib/unilib/unistrip.cpp
        unilib/unilib/unistrip.h
        unilib/unilib/utf16.cpp
        unilib/unilib/utf16.h
        unilib/unilib/utf8.cpp
        unilib/unilib/utf8.h
        unilib/unilib/version.cpp
        unilib/unilib/version.h
        main.cpp)
