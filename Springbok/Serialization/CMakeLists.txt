set(H_FILES ValueTree.h XINI.h ToString.h ToString_Types.h)
set(CPP_FILES ValueTree.cpp XINI.cpp)
add_library(sbSerialization OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbSerialization PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbSerialization PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbSerialization PROPERTY OBJ_INSTALL_LOCATION Serialization)

ADD_SSTEST_FILE(SpringbokTest XINI_Test.cpp ToString_Test.cpp)