find_package(GLFW REQUIRED)

set(H_FILES FileInfo.h PreciseClock.h InputDevice.h ButtonPressEvent.h InputMonitor.h GameSurface.h)
set(CPP_FILES FileInfo.cpp PreciseClock.cpp InputDevice.cpp ButtonPressEvent.cpp)

add_subdirectory(GLFW)

add_library(sbPlatform STATIC ${CPP_FILES} ${H_FILES} $<TARGET_OBJECTS:sbPlatformGLFW>)
set_property(TARGET sbPlatform PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(sbPlatform ${GLFW_LIBRARIES})

set_property(TARGET sbPlatform PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbPlatform PUBLIC_HEADER DESTINATION include/Springbok/Platform ARCHIVE DESTINATION lib/Springbok)