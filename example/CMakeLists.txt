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
SET(CMAKE_CXX_FLAGS "-m64 -std=c++20 -fconcepts -s -Wall -Wno-unused-variable -Os")

include(GNUInstallDirs)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CURRY curry)
set(TENSOR tensor)
set(MONSTER monster)
set(OVERVIEW overview)
set(OBJECT_POOL object_pool)
set(THREAD_POOL thread_pool)

add_executable(${CURRY} curry.cpp)
add_executable(${TENSOR} tensor.cpp)
add_executable(${MONSTER} monster.cpp)
add_executable(${OVERVIEW} overview.cpp)
add_executable(${OBJECT_POOL} object_pool.cpp)
add_executable(${THREAD_POOL} thread_pool.cpp)

target_link_libraries(${THREAD_POOL} pthread)

install(TARGETS ${CURRY} ${TENSOR} ${MONSTER} ${OVERVIEW} ${OBJECT_POOL} ${THREAD_POOL} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
