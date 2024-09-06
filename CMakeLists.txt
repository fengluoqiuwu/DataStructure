cmake_minimum_required(VERSION 3.29)
project(DataStructure)

# 设置 C++ 标准版本
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_VERBOSE_MAKEFILE ON)

include(FetchContent)

# 下载 nlohmann_json
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG main  # 可以根据需要设置特定版本或使用最新的 release 标签
)

FetchContent_MakeAvailable(nlohmann_json)

# 下载GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main  # 使用最新主分支
)

FetchContent_MakeAvailable(googletest)

# 包含子目录
#add_subdirectory(lib/algorithms)  # 添加库
add_subdirectory(lib/data_structure)  # 添加库
#add_subdirectory(exe)  # 添加应用程序

