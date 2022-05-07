cmake_minimum_required(VERSION 3.20)
cmake_policy(SET CMP0054 NEW)
project(PathTracer)

FILE(GLOB cmakes ${CMAKE_SOURCE_DIR}/cmake/*.cmake)
FOREACH(cmake ${cmakes})
    INCLUDE(${cmake})
ENDFOREACH(cmake)

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
