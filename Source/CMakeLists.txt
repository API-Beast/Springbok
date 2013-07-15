find_package(OpenGL REQUIRED)
find_package(OpenAL REQUIRED)


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

set(CORE_SOURCES Core/AssetManager.cpp)
set(AUDIO_SOURCES Audio/SoundInstance.cpp Audio/SoundManager.cpp Audio/SoundSample.cpp Audio/SoundSource.cpp)
set(GRAPHICS_SOURCES Graphics/Image.cpp Graphics/RenderManager.cpp Graphics/Texture.cpp Graphics/ColorPalette.cpp)
set(GENERIC_SOURCES Generic/ObjectPointer.cpp)
set(DEPENDENCY_SOURCES Dependencies/lodepng.cpp)
set(GEOMETRY_SOURCES Geometry/Angle.cpp Geometry/CollisionDetection.cpp)
ADD_SSTEST_FILE(libBeastTest Math/Operations_Tests.cpp Generic/ObjectPointer_Examples.cpp)
set(MATH_SOURCES)

set(ALL_SOURCES ${CORE_SOURCES} ${AUDIO_SOURCES} ${GENERIC_SOURCES} ${MATH_SOURCES} ${GEOMETRY_SOURCES} ${GRAPHICS_SOURCES} ${DEPENDENCY_SOURCES})
file(GLOB_RECURSE ALL_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/Springbok/Config.h *.h *.hpp)

add_subdirectory(Platform)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${OPENAL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
add_library(Springbok SHARED ${ALL_SOURCES} ${ALL_HEADERS})
target_link_libraries(Springbok Platform ${OPENGL_LIBRARIES} ${OPENAL_LIBRARY})