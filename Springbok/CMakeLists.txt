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

option(BUILD_STATIC "If ON Springbok will be build as static lib instead." ON)

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
add_subdirectory(Parsing)
add_subdirectory(Containers)
add_subdirectory(Procedural)
add_subdirectory(Dependencies)
add_subdirectory(Utils)
add_subdirectory(Shapes)
add_subdirectory(Types)

set(SUBTARGETS sbAnimation sbAudio sbContainers sbDependencies sbGeneric sbGeometry sbGraphics sbMath sbParsing sbPlatform sbProcedural sbResources sbUtils sbShapes sbTypes)
set(COMBINED_HEADERS Animation.hpp Audio.hpp Containers.hpp Generic.hpp Geometry.hpp Graphics.hpp Math.hpp Parsing.hpp Platform.hpp Procedural.hpp Resources.hpp Shapes.hpp Utils.hpp Types.hpp)

RESOLVE_SUBTARGET_CHILDREN(SUBTARGETS ${SUBTARGETS})
GET_SUBTARGET_OBJECTS(SUBTARGETS_EXPANDED ${SUBTARGETS})

if(BUILD_STATIC)
	add_library(Springbok STATIC ${SUBTARGETS_EXPANDED} ${COMBINED_HEADERS})
else()
	set_property(TARGET ${SUBTARGETS} PROPERTY POSITION_INDEPENDENT_CODE ON)
	add_library(Springbok SHARED ${SUBTARGETS_EXPANDED} ${COMBINED_HEADERS})
endif()

LINK_SUBTARGET_DEPENDENCIES(Springbok ${SUBTARGETS})
target_link_libraries(Springbok)

install(TARGETS Springbok LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Springbok/Config.h ${COMBINED_HEADERS}
				DESTINATION include/Springbok)
INSTALL_SUBTARGET_HEADERS(include/Springbok ${SUBTARGETS})