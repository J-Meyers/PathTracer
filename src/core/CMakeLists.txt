add_library(core
        camera.h
        camera.cpp
        scene.cpp
        scene.h
        renderer.cpp
        renderer.h
        isect.h
        isect.cpp
        material.cpp
        material.h
        renderer.h
        renderer.cpp
        scene_object.cpp
        scene_object.h
        spectrum.cpp
        spectrum.h)

target_include_directories(core INTERFACE ..)
target_link_libraries(core geometry)