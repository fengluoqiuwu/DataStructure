# 定义项目
project(DataStructure)

# 定义路径
file(GLOB SRC src/*.cpp)

# 定义库
add_library(DataStructure STATIC ${SRC})

# 指定公共头文件目录（外部代码可以访问）
target_include_directories(DataStructure
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/public_libraries>  # 构建时
        $<INSTALL_INTERFACE:include/public_libraries>  # 安装后
        ${CMAKE_SOURCE_DIR}/include/data_structure  # 私有头文件目录，仅库内部访问
)
target_link_libraries(DataStructure PRIVATE nlohmann_json::nlohmann_json)

# 测试部分
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # 添加测试
    enable_testing()
    file(GLOB TEST_SRC test/*.cpp)
    add_executable(DataStructureTest ${TEST_SRC}
            test/linked_list_test.cpp)
    target_link_libraries(DataStructureTest PRIVATE DataStructure nlohmann_json::nlohmann_json gtest gtest_main)
    add_test(NAME DataStructureTest COMMAND DataStructureTest)
endif()