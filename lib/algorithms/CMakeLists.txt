# 定义路径
file(GLOB SRC ${PROJECT_SOURCE_DIR}/lib/algorithms/*.cpp)

# 定义库
add_library(Algorithms STATIC ${SRC})

# 指定库的头文件目录，供其他目标使用
target_include_directories(Algorithms PUBLIC ${CMAKE_SOURCE_DIR}/include)