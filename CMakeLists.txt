cmake_minimum_required(VERSION 3.16.3)
project(Project3)

set(CMAKE_CXX_STANDARD 14)

include_directories(./libraries/bridges/include)
link_directories(./libraries/bridges/lib)

include_directories(./libraries/curl/include)
link_directories(./libraries/curl/lib)

add_executable(Project3 main.cpp fencer.h fencer.cpp graph.h graph.cpp)
target_link_libraries(Project3 libcurl.lib)
