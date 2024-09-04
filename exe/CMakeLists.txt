# 定义可执行文件
add_executable(MyExecutable main.cpp)

# 链接库到可执行文件
target_link_libraries(MyExecutable PRIVATE Algorithms DataStructure)