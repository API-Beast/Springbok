set(H_FILES Angle.h Angle_constexpr.h Line2.h Rect.h Vec2.h  Line2_Templates.hpp Rect_Templates.hpp Vec2_Templates.hpp BoundingShapes.h)
set(CPP_FILES Angle.cpp BoundingShapes.cpp)
add_library(sbGeometry OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGeometry PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGeometry PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGeometry PROPERTY OBJ_INSTALL_LOCATION Geometry)

ADD_SSTEST_FILE(SpringbokTest Angle_Tests.cpp BoundingShapes_Tests.cpp Vec2_Tests.cpp)