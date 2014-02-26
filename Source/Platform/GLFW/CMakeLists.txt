include_directories(${GLFW_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
add_library(sbPlatformGLFW OBJECT ButtonSpecs.cpp GameSurface.cpp InputMonitor.cpp)
set_property(TARGET sbPlatformGLFW PROPERTY POSITION_INDEPENDENT_CODE ON)