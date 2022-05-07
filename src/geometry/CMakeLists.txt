add_library(geometry test.h test.cpp ray.cpp ray.h)
target_include_directories(geometry INTERFACE ..)
