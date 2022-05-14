cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0054 NEW)
project(PathTracer)

find_program(CONAN conan)
if (NOT CONAN)
    message(FATAL_ERROR "Needs conan package manager: please visit https://conan.io and install")
endif ()

FILE(GLOB cmakes ${CMAKE_SOURCE_DIR}/cmake/*.cmake)
FOREACH (cmake ${cmakes})
    INCLUDE(${cmake})
ENDFOREACH (cmake)

conan_check(VERSION 1.14.4 REQUIRED)
conan_add_remote(NAME bincrafters INDEX 1
        URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

add_subdirectory(src)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_package(OpenGL REQUIRED)
find_package(TBB REQUIRED)

add_definitions(${OPENGL_DEFINITIONS})

#link {OPENGL_gl_Library}
# link TBB::tbb
# link ${OPENGL_glu_LIBRARY}
# link Threads::Threads
