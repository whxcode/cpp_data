#!/bin/bash

# 运行 cmake
cmake ..

# 运行 make
make

echo "=====================start================="
# 运行程序
time ./ProjectName
