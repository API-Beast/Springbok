find_package(OpenGL REQUIRED)

set(H_FILES ProxyRender.h RenderTarget.h BatchRenderer.h BatchRenderer_Templates.hpp GLES2.h BitmapFont.h Color.h Image.h RenderContext2D.h VertexStruct.h Texture.h Transform2D.h Shader.h ShaderProgram.h Transform2D_Templates.hpp)
set(CPP_FILES GLES2.cpp BitmapFont.cpp Color.cpp Image.cpp RenderContext2D.cpp VertexStruct.cpp Texture.cpp Transform2D.cpp Shader.cpp ShaderProgram.cpp)

include_directories(${OPENGL_INCLUDE_DIR})
add_library(sbGraphics OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGraphics PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGraphics PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGraphics PROPERTY OBJ_INSTALL_LOCATION Graphics)
set_property(TARGET sbGraphics PROPERTY OBJ_DEPENDENCIES ${OPENGL_LIBRARY})

#ADD_SSTEST_FILE(SpringbokTest file.cpp)