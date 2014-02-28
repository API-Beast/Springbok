if(NOT SPRINGBOK_HTML5)
  find_package(OpenGL REQUIRED)
endif()

set(H_FILES BitmapFont.h Color.h Image.h RenderContext.h Texture.h GLTypes.h Shader.h Camera.h GraphicsBatch.h RenderParameters.h)
set(CPP_FILES BitmapFont.cpp Color.cpp Image.cpp RenderContext.cpp Texture.cpp Shader.cpp Camera.cpp GraphicsBatch.cpp RenderParameters.cpp)

include_directories(${OPENGL_INCLUDE_DIR})
add_library(sbGraphics OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGraphics PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGraphics PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGraphics PROPERTY OBJ_INSTALL_LOCATION Graphics)
set_property(TARGET sbGraphics PROPERTY OBJ_DEPENDENCIES ${OPENGL_LIBRARY})

#ADD_SSTEST_FILE(SpringbokTest file.cpp)
