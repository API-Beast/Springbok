set(H_FILES ObjectPointer.h ObjectPointer_Templates.hpp LogicChain.h LogicChain_Templates.hpp PointerGuard.h)
set(CPP_FILES ObjectPointer.cpp)
add_library(sbGeneric OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbGeneric PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbGeneric PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbGeneric PROPERTY OBJ_INSTALL_LOCATION Generic)

ADD_SSTEST_FILE(SpringbokTest ObjectPointer_Tests.cpp)