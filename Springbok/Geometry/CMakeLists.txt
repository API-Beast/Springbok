set(H_FILES Angle.h Angle_constexpr.h Rect.h Mat2.h Vec3.h Vec3_Templates.hpp Vec2.h Vec2_Templates.hpp Rect_Templates.hpp BoundingShapes.h GeometryView.h)
set(CPP_FILES Angle.cpp BoundingShapes.cpp)
add_library(sbGeometry OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGeometry PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGeometry PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGeometry PROPERTY OBJ_INSTALL_LOCATION Geometry)

ADD_SSTEST_FILE(SpringbokTest Angle_Tests.cpp BoundingShapes_Tests.cpp Vec2_Tests.cpp GeometryView_Tests.cpp)