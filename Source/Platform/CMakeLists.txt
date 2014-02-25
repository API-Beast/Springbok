set(H_FILES FileInfo.h PreciseClock.h InputDevice.h ButtonPressEvent.h InputMonitor.h GameSurface.h)
set(CPP_FILES FileInfo.cpp PreciseClock.cpp InputDevice.cpp ButtonPressEvent.cpp)

if(SPRINGBOK_HTML5)
	add_subdirectory(SDL)
else(SPRINGBOK_HTML5)
	find_package(GLFW REQUIRED)
	add_subdirectory(GLFW)
endif(SPRINGBOK_HTML5)

add_library(sbPlatform OBJECT ${CPP_FILES} ${H_FILES})

set_property(TARGET sbPlatform PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbPlatform PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbPlatform PROPERTY OBJ_INSTALL_LOCATION Platform)

if(SPRINGBOK_HTML5)
	set_property(TARGET sbPlatform PROPERTY OBJ_CHILDREN sbPlatformSDL)
else(SPRINGBOK_HTML5)
	set_property(TARGET sbPlatform PROPERTY OBJ_DEPENDENCIES ${GLFW_LIBRARIES})
	set_property(TARGET sbPlatform PROPERTY OBJ_CHILDREN sbPlatformGLFW)
endif(SPRINGBOK_HTML5)