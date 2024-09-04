# 定义可执行文件
add_executable(MyExecutable main.cpp
        ../include/MyLibrary/algorithms.h
        ../include/MyLibrary/data_structure.h)

# 链接库到可执行文件
target_link_libraries(MyExecutable PRIVATE MyLibrary)