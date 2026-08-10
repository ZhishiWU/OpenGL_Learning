# clean.cmake
file(REMOVE_RECURSE "${CMAKE_SOURCE_DIR}/build")
message(STATUS "build folder cleared, next build will be a full rebuild")