# parser generators (flex,yacc/bison,ragel,lemon,..)

find_package(RAGEL    REQUIRED)
find_package(LEMON    REQUIRED)
find_package(Readline REQUIRED)

file(GLOB R
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.ragel
    lib/src/*.ragel lib/*/src/*.ragel
)

file(GLOB M
    RELATIVE ${CMAKE_SOURCE_DIR}
    src/*.lemon
    lib/src/*.lemon lib/*/src/*.lemon
)

foreach(RAGEL_FILE ${R})
    string(REGEX REPLACE ".+\/(.+)\.ragel$" "${CMAKE_BINARY_DIR}/\\1.ragel.cpp"
        RAGEL_CPP           ${RAGEL_FILE})
    list(APPEND CP          ${RAGEL_CPP})
    add_custom_command(
        OUTPUT              ${RAGEL_CPP}
        DEPENDS             ${RAGEL_FILE}
        WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
        COMMAND             ${RAGEL_EXECUTABLE}
        ARGS                -C -G2 -o ${RAGEL_CPP} ${RAGEL_FILE}
    )
endforeach()

foreach(LEMON_FILE ${M})
    #
    string(REGEX REPLACE ".+\/(.+)\.lemon$" "${CMAKE_BINARY_DIR}/\\1.lemon.cpp"
        LEMON_CPP           ${LEMON_FILE})
    list(APPEND CP          ${LEMON_CPP})
    string(REGEX REPLACE ".+\/(.+)\.lemon$" "${CMAKE_BINARY_DIR}/\\1.lemon.hpp"
        LEMON_HPP           ${LEMON_FILE})
    list(APPEND HP          ${LEMON_HPP})
    string(REGEX REPLACE ".+\/(.+)\.lemon$" "${CMAKE_BINARY_DIR}/\\1.lemon.out"
        LEMON_OUT           ${LEMON_FILE})
    list(APPEND OP          ${LEMON_OUT})
    #
    string(REGEX REPLACE ".+\/(.+)\.lemon$" "${CMAKE_BINARY_DIR}/\\1.c"
        LEMON_C             ${LEMON_FILE})
    string(REGEX REPLACE ".+\/(.+)\.lemon$" "${CMAKE_BINARY_DIR}/\\1.h"
        LEMON_H             ${LEMON_FILE})
    string(REGEX REPLACE ".+\/(.+)\.lemon$" "${CMAKE_BINARY_DIR}/\\1.out"
        LEMON_O             ${LEMON_FILE})
    add_custom_command(
        OUTPUT              ${LEMON_C} ${LEMON_H} ${LEMON_O}
        DEPENDS             ${LEMON_FILE}
        WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
        COMMAND             ${LEMON_EXECUTABLE}
        ARGS                -l -d${CMAKE_BINARY_DIR} ${LEMON_FILE}
    )
    add_custom_command(
        OUTPUT              ${LEMON_CPP}
        DEPENDS             ${LEMON_C}
        WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
        COMMAND             mv
        ARGS                ${LEMON_C} ${LEMON_CPP}
    )
    add_custom_command(
        OUTPUT              ${LEMON_HPP}
        DEPENDS             ${LEMON_H}
        WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
        COMMAND             mv
        ARGS                ${LEMON_H} ${LEMON_HPP}
    )
    add_custom_command(
        OUTPUT              ${LEMON_OUT}
        DEPENDS             ${LEMON_O}
        WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
        COMMAND             mv
        ARGS                ${LEMON_O} ${LEMON_OUT}
    )
endforeach()
