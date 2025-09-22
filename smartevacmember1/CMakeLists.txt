cmake_minimum_required(VERSION 3.10)
project(SmartDisasterEvacuationPlanner)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(SmartDisasterEvacuationPlanner src/main.cpp src/graph.cpp src/dijkstra.cpp)
