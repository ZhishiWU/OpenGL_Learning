# build_and_run.cmake - Build and run
execute_process(
    COMMAND ${CMAKE_COMMAND} -P build.cmake
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RESULT_VARIABLE ret
)
if(NOT ret EQUAL 0)
    message(FATAL_ERROR "Build failed.")
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} -P run.cmake
    WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    RESULT_VARIABLE ret
)