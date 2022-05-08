add_library(geometry
        ray.cpp
        ray.h
        orthonormal_basis.cpp
        orthonormal_basis.h
        constants.h
        transform_node.cpp
        transform_node.h
        bbox.cpp
        bbox.h)
target_include_directories(geometry INTERFACE ..)
