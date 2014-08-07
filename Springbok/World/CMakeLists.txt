set(H_FILES   TileMapIterator.h)
set(CPP_FILES TileMapIterator.cpp)
add_library(sbWorld OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbWorld PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbWorld PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbWorld PROPERTY OBJ_INSTALL_LOCATION World)

ADD_SSTEST_FILE(SpringbokTest)