cmake_minimum_required(VERSION 3.16)

project(CppRenderer3D LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# minifb 子项目：关闭其自带的 examples 与 version_info，避免被纳入本项目构建
set(MINIFB_BUILD_EXAMPLES OFF CACHE BOOL "Build minifb example programs"  )
set(MINIFB_BUILD_VERSION_INFO OFF CACHE BOOL "Build version info utility" FORCE)
add_subdirectory(minifb)

set(GLM_BUILD_TESTS OFF CACHE BOOL "Build the test programs" FORCE)
add_subdirectory(glm)

# 主项目
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
message(STATUS "SRC_LIST = ${SRC_LIST}")
add_executable(CppRenderer3D ${SRC_LIST})

# 导入库
# target_include_directories(CppRenderer3D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(CppRenderer3D PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glm)

# 链接
target_link_libraries(CppRenderer3D PRIVATE minifb glm)
