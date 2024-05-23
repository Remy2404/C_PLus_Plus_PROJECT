cmake_minimum_required(VERSION 3.26)
project(bus_system)

set(openCV_DIR "C:/Users/Admin/Downloads/Compressed/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/OpenCV-MinGW-Build-OpenCV-4.5.5-x64/x64/mingw/bin")

add_executable(Helloworld bus_system.cpp
        Brocode.cpp
        posv2.cpp
        posv3.cpp
        .vscode/W7_Queue/Queue_dsa.h
        .vscode/W7_Queue/Queue_dsa.h)

find_package(OpenCV REQUIRED)

target_link_libraries(Hello-world ${OpenCV_LIBS})
