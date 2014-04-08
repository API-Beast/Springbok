set(H_FILES BitmapFont.h Framebuffer.h Image.h Color.h SpriteRenderer.h SpriteRenderer_Templates.hpp)
set(CPP_FILES BitmapFont.cpp Framebuffer.cpp Image.cpp Color.cpp SpriteRenderer.cpp)

add_library(sbGraphics OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGraphics PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGraphics PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGraphics PROPERTY OBJ_INSTALL_LOCATION Graphics)
set_property(TARGET sbGraphics PROPERTY OBJ_CHILDREN sbGraphicsCore)

add_subdirectory(Core/)

#ADD_SSTEST_FILE(SpringbokTest file.cpp)