set(H_FILES ConfigFile.h UTF8.h UTF8_Templates.hpp Unicode.h StringParser.h StringParser_Templates.hpp)
set(CPP_FILES ConfigFile.cpp UTF8.cpp StringParser.cpp)
add_library(sbParsing STATIC ${H_FILES} ${CPP_FILES})
set_property(TARGET sbParsing PROPERTY POSITION_INDEPENDENT_CODE ON)

ADD_SSTEST_FILE(SpringbokTest UTF8_Tests.cpp StringParser_Tests.cpp ConfigFile_Tests.cpp)

set_property(TARGET sbParsing PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbParsing PUBLIC_HEADER DESTINATION include/Springbok/Parsing ARCHIVE DESTINATION lib/Springbok)