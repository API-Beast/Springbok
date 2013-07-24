## -------------------- ##
##  Configuration file  ##
## -------------------- ##
# Which system? CMake should know best.
if(WIN32)
  set(SPRINGBOK_WINDOWS 1)
elseif(APPLE)
  set(SPRINGBOK_MAC 1)
elseif(UNIX)
  set(SPRINGBOK_LINUX 1)
else()
  set(SPRINGBOK_UNKNOWN 1)
endif()

include_directories(${CMAKE_CURRENT_BINARY_DIR})
configure_file(Config.h.in ${CMAKE_CURRENT_BINARY_DIR}/Springbok/Config.h)

## -------------------- ##
##       Library        ##
## -------------------- ##

add_subdirectory(Animation)
add_subdirectory(Audio)
add_subdirectory(Generic)
add_subdirectory(Geometry)
add_subdirectory(Graphics)
add_subdirectory(Math)
add_subdirectory(Platform)
add_subdirectory(Resources)

add_library(Springbok SHARED dummy.cpp Dependencies/lodepng.cpp)
target_link_libraries(Springbok sbAnimation sbAudio sbGeneric sbGeometry sbGraphics sbMath sbPlatform sbResources)