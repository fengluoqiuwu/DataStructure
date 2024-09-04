cmake_minimum_required(VERSION 3.29)
project(DataStructure)

# 设置 C++ 标准版本
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

# 包含子目录
add_subdirectory(lib)  # 添加库
add_subdirectory(exe)  # 添加应用程序
