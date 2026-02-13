cmake_minimum_required(VERSION 3.20)
project(aegis_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aegis 
	src/main.cpp 
	src/jwt/JwtUtils.cpp
)
