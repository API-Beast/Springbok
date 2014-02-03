find_package(OpenGL REQUIRED)

set(H_FILES Color.h ColorPalette.h Image.h RenderContext.h Texture.h)
set(CPP_FILES Color.cpp ColorPalette.cpp Image.cpp RenderContext.cpp Texture.cpp)

include_directories(${OPENGL_INCLUDE_DIR})
add_library(sbGraphics STATIC ${H_FILES} ${CPP_FILES})
target_link_libraries(sbGraphics sbResources ${OPENGL_LIBRARY})

set_property(TARGET sbGraphics PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbGraphics PUBLIC_HEADER DESTINATION include/Springbok/Graphics ARCHIVE DESTINATION lib/Springbok)

#ADD_SSTEST_FILE(SpringbokTest file.cpp)