add_library(geometry
        ray.cpp
        ray.h
        orthonormal_basis.cpp
        orthonormal_basis.h
        epsilon.h
        transform_node.cpp
        transform_node.h
        bbox.cpp
        bbox.h)
target_include_directories(geometry INTERFACE ..)
