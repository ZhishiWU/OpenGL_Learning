# build.cmake 增量编译版本
set(BUILD_DIR "${CMAKE_SOURCE_DIR}/build")

# build不存在才创建；存在就直接复用，不删除
if(NOT EXISTS ${BUILD_DIR})
    file(MAKE_DIRECTORY ${BUILD_DIR})
endif()

# configure，CMake会自动检测是否需要重新配置
execute_process(
    COMMAND ${CMAKE_COMMAND} ..
    WORKING_DIRECTORY "${BUILD_DIR}"
    RESULT_VARIABLE ret
)
if(NOT ret EQUAL 0)
    message(FATAL_ERROR "CMake configure failed")
endif()

# --build 自动增量：只编译改动过的文件
execute_process(
    COMMAND ${CMAKE_COMMAND} --build . --parallel
    WORKING_DIRECTORY "${BUILD_DIR}"
    RESULT_VARIABLE ret
)
if(NOT ret EQUAL 0)
    message(FATAL_ERROR "Build failed")
endif()

message(STATUS "==== Build Success! ====")
if(WIN32)
    message(STATUS "Output exe: build/Debug/opengl_glfw.exe")
else()
    message(STATUS "Output binary: build/opengl_glfw")
endif()