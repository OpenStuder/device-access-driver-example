cmake_minimum_required(VERSION 3.0)
project(ExampleExtension)
find_package(SIExtension REQUIRED)
si_add_extension_driver(ExampleExtension example.h example.cpp)
