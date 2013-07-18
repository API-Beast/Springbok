set(H_FILES ObjectPointer.h ObjectPointer_Templates.hpp)
set(CPP_FILES ObjectPointer.cpp ObjectPointer_Examples.cpp)
add_library(sbGeneric STATIC ${H_FILES} ${CPP_FILES})
ADD_SSTEST_FILE(SpringbokTest ObjectPointer_Examples.cpp)