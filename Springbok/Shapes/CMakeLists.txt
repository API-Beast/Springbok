set(H_FILES LineShape.h LineShape_Templates.hpp)
set(CPP_FILES LineShape.cpp)
add_library(sbShapes OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbShapes PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbShapes PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbShapes PROPERTY OBJ_INSTALL_LOCATION Shapes)