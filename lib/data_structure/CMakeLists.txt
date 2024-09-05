# 定义路径
file(GLOB SRC ${PROJECT_SOURCE_DIR}/lib/data_structure/*.cpp)

# 定义库
add_library(DataStructure STATIC ${SRC}
        array.cpp
        linked_list.cpp)

# 指定库的头文件目录，供其他目标使用
target_include_directories(DataStructure PUBLIC ${CMAKE_SOURCE_DIR}/include)