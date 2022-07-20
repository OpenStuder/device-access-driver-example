cmake_minimum_required(VERSION 3.0)
project(ExampleStorage)
find_package(SIStorage REQUIRED)
si_add_storage_driver(ExampleStorage example.h example.cpp)
