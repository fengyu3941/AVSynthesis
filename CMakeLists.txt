cmake_minimum_required(VERSION 2.6)
project(AVSynthesis)
add_executable(AVSynthesis AVSynthesis.cpp)
install(TARGETS AVSynthesis DESTINATION bin)