set(H_FILES Path.h MemoryBlock.h DataBlock.h DataBlock_Templates.hpp Angle.h Angle_constexpr.h ObjectPointer.h ObjectPointer_Templates.hpp PointerGuard.h Vec2.h Vec2_Templates.hpp Vec3.h Vec3_Templates.hpp Vec4.h Vec4_Templates.hpp)
set(CPP_FILES Path.cpp MemoryBlock.cpp Angle.cpp ObjectPointer.cpp ResourceManager.cpp)
add_library(sbFoundation OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbFoundation PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbFoundation PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbFoundation PROPERTY OBJ_INSTALL_LOCATION Foundation)

ADD_SSTEST_FILE(SpringbokTest Angle_Tests.cpp Vec2_Tests.cpp ObjectPointer_Tests.cpp)