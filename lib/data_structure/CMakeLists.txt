# 定义项目
cmake_minimum_required(VERSION 3.29)
project(DataStructure)

# 定义路径
file(GLOB SRC src/*.cpp)

# 定义库
add_library(DataStructure STATIC ${SRC})

# 指定公共头文件目录（外部代码可以访问）
target_include_directories(DataStructure
        PUBLIC
        ${CMAKE_SOURCE_DIR}/include/public_libraries
        ${CMAKE_SOURCE_DIR}/include/data_structure
        ${CMAKE_SOURCE_DIR}/include/data_structure/linear
)

target_link_libraries(DataStructure PRIVATE nlohmann_json::nlohmann_json)

# 测试部分
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 添加测试
    enable_testing()
    file(GLOB TEST_SRC
            test/linear/*.cpp
    )
    add_executable(DataStructureTest ${TEST_SRC})
    target_link_libraries(DataStructureTest PRIVATE DataStructure nlohmann_json::nlohmann_json gtest gtest_main)
    add_test(NAME DataStructureTest COMMAND DataStructureTest)
endif()