set(H_FILES lodepng.h stb_vorbis.h)
set(CPP_FILES lodepng_config.cpp stb_vorbis_config.cpp)
add_library(sbDependencies STATIC ${H_FILES} ${CPP_FILES})
set_property(TARGET sbDependencies PROPERTY POSITION_INDEPENDENT_CODE ON)

#set_property(TARGET sbDependencies PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
#set_property(TARGET sbGeneric PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
#set_property(TARGET sbGeneric PROPERTY OBJ_INSTALL_LOCATION Dependencies)

#ADD_SSTEST_FILE(SpringbokTest ObjectPointer_Examples.cpp)