include_directories(${GLFW_INCLUDE_DIR})
add_library(sbPlatformGLFW STATIC ButtonSpecs.cpp GameSurface.cpp InputMonitor.cpp)
target_link_libraries(sbPlatformGLFW sbPlatform ${GLFW_LIBRARIES})