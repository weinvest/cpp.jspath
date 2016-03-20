cmake_minimum_required(VERSION 2.8)
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(BUILD_SHARED_LIBS ON)

#INCLUDE(cotire)

project(jspath)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Werror=uninitialized -Werror=return-type")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
