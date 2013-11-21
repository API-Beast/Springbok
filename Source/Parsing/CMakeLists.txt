set(H_FILES ConfigFile.h UTF8Decoder.h StringParser.h)
set(CPP_FILES ConfigFile.cpp UTF8Decoder.cpp StringParser.cpp)
add_library(sbParsing STATIC ${H_FILES} ${CPP_FILES})

ADD_SSTEST_FILE(SpringbokTest UTF8Decoder_Tests.cpp)