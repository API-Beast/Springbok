set(H_FILES ObjectPointer.h ObjectPointer_Templates.hpp Containers/SimpleList.h Containers/SimpleList_Templates.hpp Containers/Ringbuffer.h Structures/Associative.h Structures/SkipList.h Structures/SkipList_Templates.hpp)
set(CPP_FILES ObjectPointer.cpp)
add_library(sbGeneric STATIC ${H_FILES} ${CPP_FILES})
ADD_SSTEST_FILE(SpringbokTest ObjectPointer_Examples.cpp Containers/SimpleList_Examples.cpp)