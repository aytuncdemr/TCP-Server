cmake_minimum_required(VERSION 3.10.0)

project(TCPServer)

add_executable(TCPServer main.cpp ./src/Server.cpp)

target_include_directories(TCPServer PRIVATE ./include)

target_link_libraries(TCPServer wsock32)