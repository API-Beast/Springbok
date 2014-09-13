set(H_FILES   Noise.h   TileMapIterator.h)
set(CPP_FILES Noise.cpp TileMapIterator.cpp)
add_library(sbExperimental OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbExperimental PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbExperimental PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbExperimental PROPERTY OBJ_INSTALL_LOCATION Experimental)