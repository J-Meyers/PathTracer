add_library(parser parser.h parser.cpp material_params.h)
target_link_libraries(parser CONAN_PKG::ctre geometry)
target_include_directories(parser INTERFACE ..)