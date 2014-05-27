set(H_FILES Logic.h Logic_Implementation.hpp)
set(CPP_FILES)
add_library(sbGeneric OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGeneric PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGeneric PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGeneric PROPERTY OBJ_INSTALL_LOCATION Generic)