cmake_minimum_required(VERSION 3.15)
project(TCP_Calculator C)

set(CMAKE_C_STANDARD 99)

add_executable(TCP_Calculator server.c)
#add_executable(TCP_Calculator client.c)