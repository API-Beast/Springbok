include_directories(${GLFW_INCLUDE_DIR})
add_library(PlatformGLFW STATIC ButtonSpecs.cpp GameSurface.cpp InputMonitor.cpp)
target_link_libraries(PlatformGLFW Platform ${GLFW_LIBRARIES})