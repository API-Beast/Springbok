set(H_FILES Angle.h Line2.h Rect.h Vec2.h  Line2_Templates.hpp Rect_Templates.hpp Vec2_Templates.hpp)
set(CPP_FILES Angle.cpp)
add_library(sbGeometry STATIC ${H_FILES} ${CPP_FILES})
set_property(TARGET sbGeometry PROPERTY POSITION_INDEPENDENT_CODE ON)
#ADD_SSTEST_FILE(SpringbokTest file.cpp)

set_property(TARGET sbGeometry PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbGeometry PUBLIC_HEADER DESTINATION include/Springbok/Geometry ARCHIVE DESTINATION lib/Springbok)