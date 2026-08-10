# run.cmake - Run compiled executable
set(EXE_DIR "${CMAKE_SOURCE_DIR}/build")

if(WIN32)
    set(EXE_PATH "${EXE_DIR}/Debug/opengl_glfw.exe")
elseif(UNIX)
    set(EXE_PATH "${EXE_DIR}/opengl_glfw")
endif()

if(NOT EXISTS ${EXE_PATH})
    message(FATAL_ERROR "Executable not found. Please run 'cmake -P build.cmake' first to build.")
endif()

message(STATUS "==== Run Program ====")
message(STATUS "Launching: ${EXE_PATH}")

execute_process(
    COMMAND ${EXE_PATH}
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RESULT_VARIABLE ret
)

if(NOT ret EQUAL 0)
    message(FATAL_ERROR "Program exited abnormally, return code: ${ret}")
endif()

message(STATUS "==== Program finished ====")