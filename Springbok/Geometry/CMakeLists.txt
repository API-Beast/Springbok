set(H_FILES Rect.h Rect_Templates.hpp BoundingShapes.h GeometryView.h)
set(CPP_FILES BoundingShapes.cpp)
add_library(sbGeometry OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGeometry PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGeometry PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGeometry PROPERTY OBJ_INSTALL_LOCATION Geometry)

ADD_SSTEST_FILE(SpringbokTest GeometryView_Tests.cpp)