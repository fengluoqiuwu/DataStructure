cmake_minimum_required(VERSION 3.29)
project(DataStructure)

# 设置 C++ 标准版本
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(external_libraries/json-master)
add_subdirectory(external_libraries/googletest-main)

# 包含子目录
#add_subdirectory(lib/algorithms)  # 添加库
add_subdirectory(lib/data_structure)  # 添加库
#add_subdirectory(exe)  # 添加应用程序

