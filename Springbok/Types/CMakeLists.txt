set(H_FILES Angle.h Angle_constexpr.h Color.h Mat2.h ObjectPointer.h ObjectPointer_Templates.hpp PointerGuard.h Range.h Range_Templates.hpp Rect.h Vec2.h Vec2_Templates.hpp Vec3.h Vec3_Templates.hpp Vec4.h Vec4_Templates.hpp)
set(CPP_FILES Angle.cpp ObjectPointer.cpp Rect.cpp Color.cpp)
add_library(sbTypes OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbTypes PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbTypes PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbTypes PROPERTY OBJ_INSTALL_LOCATION Types)

ADD_SSTEST_FILE(SpringbokTest Color_Tests.cpp Angle_Tests.cpp Vec2_Tests.cpp Range_Tests.cpp ObjectPointer_Tests.cpp)