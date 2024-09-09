#!/bin/bash

# 运行 cmake
cd build

cmake ..

# 运行 make
make

echo "=====================start================="
# 运行程序
time ./ProjectName

cd ../

# 当 .compile_commands 不存在时

if [ ! -f "./compile_commands.json" ]; then
	echo "compile_commands.json is not exist"
	exit 0
fi
