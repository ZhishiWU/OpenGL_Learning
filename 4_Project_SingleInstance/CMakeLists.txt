cmake_minimum_required(VERSION 3.12)

# 工程名称
project(OpenGL_GLFW)

# Windows才设置utf8编译选项；Linux不能识别 /utf‑8
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 最低c++标准
set(CMAKE_CXX_STANDARD 17)

# 全局预编译宏
add_definitions(-DDEBUG)

# 引入glfw子项目
add_subdirectory(${CMAKE_SOURCE_DIR}/thirdParty/glfw)
# 引入wrapper子库（内部有自己的CMakeLists.txt）
add_subdirectory(${CMAKE_SOURCE_DIR}/wrapper)
# 引入application子库（内部有自己的CMakeLists.txt）
add_subdirectory(${CMAKE_SOURCE_DIR}/application)

# 生成可执行程序
add_executable(opengl_glfw
    "main.cpp"
    "glad.c"
)

# 头文件搜索路径(glad头文件)
target_include_directories(
    opengl_glfw
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
    ${CMAKE_CURRENT_SOURCE_DIR}/wrapper
    ${CMAKE_CURRENT_SOURCE_DIR}/application
)

# 链接glfw（来自源码编译，不再依赖thirdParty/lib下的glfw3.lib）
target_link_libraries(
    opengl_glfw
    PRIVATE
    glfw
    app
)

# 分平台链接OpenGL
if(WIN32)
    target_link_libraries(opengl_glfw PRIVATE opengl32.lib)
elseif(UNIX)
    find_package(OpenGL REQUIRED)
    target_link_libraries(opengl_glfw PRIVATE ${OPENGL_LIBRARIES})
endif()