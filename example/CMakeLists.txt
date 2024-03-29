#
# Copyright (c) 2011-present DeepGrace (complex dot invoke at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/deepgrace/monster
#

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-m64 -std=c++23 -s -Wall -O3")

include(GNUInstallDirs)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(ARITY arity)
set(CURRY curry)
set(TENSOR tensor)
set(MONSTER monster)
set(OVERVIEW overview)
set(OBJECT_POOL object_pool)
set(THREAD_POOL thread_pool)
set(LOOP_UNROLL loop_unroll)

set(STREAM stream)
set(IS_LAMBDA is_lambda)
set(SORT_TUPLE sort_tuple)
set(YCOMBINATOR ycombinator)
set(MEMOIZED_INVOKE memoized_invoke)
set(TUPLE_ALGORITHM tuple_algorithm)
set(COMPILER_DETECTOR compiler_detector)

add_executable(${ARITY} arity.cpp)
add_executable(${CURRY} curry.cpp)
add_executable(${TENSOR} tensor.cpp)
add_executable(${MONSTER} monster.cpp)
add_executable(${OVERVIEW} overview.cpp)
add_executable(${OBJECT_POOL} object_pool.cpp)
add_executable(${THREAD_POOL} thread_pool.cpp)
add_executable(${LOOP_UNROLL} loop_unroll.cpp)

add_executable(${STREAM} stream.cpp)
add_executable(${IS_LAMBDA} is_lambda.cpp)
add_executable(${SORT_TUPLE} sort_tuple.cpp)
add_executable(${YCOMBINATOR} ycombinator.cpp)
add_executable(${MEMOIZED_INVOKE} memoized_invoke.cpp)
add_executable(${TUPLE_ALGORITHM} tuple_algorithm.cpp)
add_executable(${COMPILER_DETECTOR} compiler_detector.cpp)

target_link_libraries(${THREAD_POOL} pthread)

install(TARGETS ${ARITY} ${CURRY} ${TENSOR} ${MONSTER} ${OVERVIEW} ${OBJECT_POOL} ${THREAD_POOL} ${YCOMBINATOR} ${LOOP_UNROLL} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
install(TARGETS ${STREAM} ${IS_LAMBDA} ${SORT_TUPLE} ${MEMOIZED_INVOKE} ${TUPLE_ALGORITHM} ${COMPILER_DETECTOR} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
