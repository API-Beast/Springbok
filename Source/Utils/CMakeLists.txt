set(H_FILES CliArgumentParser.h Debug.h)
set(CPP_FILES CliArgumentParser.cpp Debug.cpp)
add_library(sbUtils OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbUtils PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbUtils PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbUtils PROPERTY OBJ_INSTALL_LOCATION Utils)

ADD_SSTEST_FILE(SpringbokTest CliArgumentParser_Test.cpp)