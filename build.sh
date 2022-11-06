#!/bin/bash

dst=/tmp
path=example

flags=(-I include -m64 -std=c++23 -s -Wall -O3)
executables=(arity curry tensor object_pool is_lambda stream ycombinator sort_tuple memoized_invoke tuple_algorithm compiler_detector loop_unroll)

for bin in ${executables[@]}; do
      g++ "${flags[@]}" -o ${dst}/${bin} ${path}/${bin}.cpp
done

for bin in monster overview; do
      g++ "${flags[@]}" -o ${dst}/${bin} ${path}/${bin}.cpp
done

g++ "${flags[@]}" -l pthread -o ${dst}/thread_pool ${path}/thread_pool.cpp

echo Please check the executables at ${dst}
