# 定义库
add_library(MyLibrary STATIC mylib.cpp)

# 指定库的头文件目录，供其他目标使用
target_include_directories(MyLibrary PUBLIC ${CMAKE_SOURCE_DIR}/include)