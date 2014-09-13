set(H_FILES Color.h Functions.h Functions_Templates.hpp KeyframeList.h KeyframeList_Templates.hpp Math.h RandomNumberGenerator.h CliArgumentParser.h)
set(CPP_FILES CliArgumentParser.cpp RandomNumberGenerator.cpp Color.cpp Functions.cpp)
add_library(sbUtils OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbUtils PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbUtils PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbUtils PROPERTY OBJ_INSTALL_LOCATION Utils)

ADD_SSTEST_FILE(SpringbokTest CliArgumentParser_Tests.cpp KeyframeList_Tests.cpp Color_Tests.cpp)