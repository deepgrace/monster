#!/bin/bash

dst=/tmp
path=example
flags=(-I include -m64 -std=c++2a -s -Wall -Os)

for bin in curry tensor object_pool; do
    g++ "${flags[@]}" -o ${dst}/${bin} ${path}/${bin}.cpp
done

for bin in monster overview; do
    g++ "${flags[@]}" -fconcepts -o ${dst}/${bin} ${path}/${bin}.cpp
done

g++ "${flags[@]}" -l pthread -o ${dst}/thread_pool ${path}/thread_pool.cpp

echo Please check the executables at ${dst}
