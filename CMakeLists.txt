cmake_minimum_required(VERSION 3.0.2)
project(circlegrid)
find_package(OpenCV 3 REQUIRED)

set(CMAKE_CXX_STANDARD 14)

add_executable(circlegrid circlegrid.cpp)
target_link_libraries(circlegrid ${OpenCV_LIBRARIES})

add_executable(calibratecam calibratecam.cpp)
target_link_libraries(calibratecam ${OpenCV_LIBRARIES})