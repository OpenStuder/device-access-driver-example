cmake_minimum_required(VERSION 3.0)
project(ExampleAuthorize)
find_package(SIAuthorize REQUIRED)
si_add_authorize_driver(ExampleAuthorize example.h example.cpp)
