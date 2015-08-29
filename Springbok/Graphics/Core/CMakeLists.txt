find_package(OpenGL REQUIRED)

set(H_FILES TextureData.h RenderTarget.h Mat2.h BatchRenderer.h BatchRenderer_Templates.hpp GLES2.h RenderContext2D.h VertexStruct.h Rect.h Texture.h Transform2D.h Shader.h ShaderProgram.h Transform2D_Templates.hpp)
set(CPP_FILES TextureData.cpp GLES2.cpp RenderContext2D.cpp VertexStruct.cpp Texture.cpp Transform2D.cpp Shader.cpp ShaderProgram.cpp Rect.cpp)

include_directories(${OPENGL_INCLUDE_DIR})
add_library(sbGraphicsCore OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGraphicsCore PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGraphicsCore PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGraphicsCore PROPERTY OBJ_INSTALL_LOCATION Graphics/Core)
set_property(TARGET sbGraphicsCore PROPERTY OBJ_DEPENDENCIES ${OPENGL_LIBRARY})

#ADD_SSTEST_FILE(SpringbokTest file.cpp)