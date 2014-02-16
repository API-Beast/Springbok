set(H_FILES Associative.h Ringbuffer.h List.h List_Templates.hpp SkipList.h SkipList_Templates.hpp View.h View_Templates.hpp)
set(CPP_FILES dummy.cpp)
add_library(sbContainers OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbContainers PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbContainers PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbContainers PROPERTY OBJ_INSTALL_LOCATION Containers)

ADD_SSTEST_FILE(SpringbokTest List_Examples.cpp)
