set(H_FILES RandomNumberGenerator.h)
set(CPP_FILES RandomNumberGenerator.cpp)
add_library(sbProcedural OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbProcedural PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbProcedural PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbProcedural PROPERTY OBJ_INSTALL_LOCATION Procedural)