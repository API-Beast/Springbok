set(H_FILES ResourceManager.h ResourceManager_Templates.hpp)
set(CPP_FILES ResourceManager.cpp)
add_library(sbResources OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbResources PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbResources PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbResources PROPERTY OBJ_INSTALL_LOCATION Resources)