find_package(OpenGL REQUIRED)

set(H_FILES Color.h ColorPalette.h Image.h RenderManager.h Texture.h)
set(CPP_FILES Color.cpp ColorPalette.cpp Image.cpp RenderManager.cpp Texture.cpp)

include_directories(${OPENGL_INCLUDE_DIR})
add_library(sbGraphics STATIC ${H_FILES} ${CPP_FILES})
target_link_libraries(sbGraphics sbCore ${OPENGL_LIBRARY})

#ADD_SSTEST_FILE(SpringbokTest file.cpp)