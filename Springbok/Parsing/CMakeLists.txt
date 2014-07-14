set(H_FILES UTF8.h UTF8_Templates.hpp Unicode.h StringParser.h StringParser_Templates.hpp Utils.h)
set(CPP_FILES UTF8.cpp StringParser.cpp)
add_library(sbParsing OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbParsing PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbParsing PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbParsing PROPERTY OBJ_INSTALL_LOCATION Parsing)

ADD_SSTEST_FILE(SpringbokTest UTF8_Tests.cpp StringParser_Tests.cpp)