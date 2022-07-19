cmake_minimum_required(VERSION 3.0)
project(ExampleDeviceAccess)
find_package(SIDeviceAccess REQUIRED)
si_add_device_access_driver(ExampleDeviceAccess example.h example.cpp)
