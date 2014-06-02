find_package(GLFW REQUIRED)

set(H_FILES FileSystem.h PreciseClock.h InputDevice.h ButtonPressEvent.h InputMonitor.h GameSurface.h)
set(CPP_FILES FileSystem.cpp PreciseClock.cpp InputDevice.cpp ButtonPressEvent.cpp)

add_subdirectory(GLFW)

add_library(sbPlatform OBJECT ${CPP_FILES} ${H_FILES})

set_property(TARGET sbPlatform PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbPlatform PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbPlatform PROPERTY OBJ_INSTALL_LOCATION Platform)
set_property(TARGET sbPlatform PROPERTY OBJ_DEPENDENCIES ${GLFW_LIBRARIES})
set_property(TARGET sbPlatform PROPERTY OBJ_CHILDREN sbPlatformGLFW)