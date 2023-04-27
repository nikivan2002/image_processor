cmake_minimum_required(VERSION 3.24)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        image_processor
        image_processor.cpp
        lib/color.cpp
        lib/color.h
        lib/controller.cpp
        lib/controller.h
        lib/image.cpp
        lib/image.h
        lib/io.cpp
        lib/io.h
        lib/filters/crop.cpp
        lib/filters/crop.h
        lib/filters/edge.cpp
        lib/filters/edge.h
        lib/filters/gs.cpp
        lib/filters/gs.h
        lib/filters/filter.h
        lib/filters/hues.cpp
        lib/filters/hues.h
        lib/filters/matrix_filter.cpp
        lib/filters/matrix_filter.h
        lib/filters/neg.cpp
        lib/filters/neg.h
        lib/filters/seamcarve.cpp
        lib/filters/seamcarve.h
        lib/filters/sharp.cpp
        lib/filters/sharp.h
        lib/filters/sobel.cpp
        lib/filters/sobel.h
        lib/parser.cpp
        lib/parser.h
)

