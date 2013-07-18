set(H_FILES Angle.h CollisionDetection.h Line2.h Rect.h Vec2.h  Line2_Templates.hpp Rect_Templates.hpp Vec2_Templates.hpp)
set(CPP_FILES Angle.cpp CollisionDetection.cpp)
add_library(sbGeometry STATIC ${H_FILES} ${CPP_FILES})
#ADD_SSTEST_FILE(SpringbokTest file.cpp)