set(H_FILES lodepng.h stb_vorbis.h)
set(CPP_FILES lodepng.cpp stb_vorbis.c)
add_library(sbDependencies OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbDependencies PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})