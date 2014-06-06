include_directories(${GLFW_INCLUDE_DIR})
add_library(sbPlatformGLFW OBJECT WindowUserData.h GameSurface.cpp InputMonitor.cpp)
set_property(TARGET sbPlatformGLFW PROPERTY POSITION_INDEPENDENT_CODE ON)