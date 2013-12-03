set(H_FILES ConfigFile.h UTF8.h StringParser.h)
set(CPP_FILES ConfigFile.cpp UTF8.cpp StringParser.cpp)
add_library(sbParsing STATIC ${H_FILES} ${CPP_FILES})

ADD_SSTEST_FILE(SpringbokTest UTF8_Tests.cpp StringParser_Tests.cpp ConfigFile_Tests.cpp)