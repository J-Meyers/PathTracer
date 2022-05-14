add_library(geometry
        ray.cpp
        ray.h
        orthonormal_basis.cpp
        orthonormal_basis.h
        constants.h
        transform_node.cpp
        transform_node.h
        bbox.cpp
        bbox.h
        light_functions.h
        light_functions.cpp
        )
target_include_directories(geometry INTERFACE ..)
