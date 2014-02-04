find_package(GLFW)

set(H_FILES FileInfo.h PreciseClock.h InputDevice.h ButtonPressEvent.h InputMonitor.h GameSurface.h)
set(CPP_FILES FileInfo.cpp PreciseClock.cpp InputDevice.cpp ButtonPressEvent.cpp)

add_library(sbPlatform STATIC ${CPP_FILES} ${H_FILES})

set_property(TARGET sbPlatform PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbPlatform PUBLIC_HEADER DESTINATION include/Springbok/Platform ARCHIVE DESTINATION lib/Springbok)

if(GLFW_FOUND)
	set(BUILD_PLATFORM 1)
	add_subdirectory(GLFW)
	target_link_libraries(sbPlatform sbPlatformGLFW)
else()
	set(BUILD_PLATFORM 0)
	message(WARNING "No Backend for Platform found.")
	message(WARNING "Please install GLFW or you won't be able to use the Input or Surface parts of the Platform module.")
endif()