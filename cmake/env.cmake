# Directories
LINK_DIRECTORIES("/usr/local/lib" "/opt/local/lib")
INCLUDE_DIRECTORIES("/usr/local/include" "/opt/local/include")
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# Enviornment configuration
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -Werror -Wextra -march=native -g -funsafe-math-optimizations)


# Packages
FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})
LINK_DIRECTORIES(${OPENGL_LIBRARY_DIRS})
ADD_DEFINITIONS(${OPENGL_DEFINITIONS})

MESSAGE(STATUS "OpenGL: ${OPENGL_LIBRARIES}")
LIST(APPEND stdgl_libraries ${OPENGL_gl_LIBRARY})
