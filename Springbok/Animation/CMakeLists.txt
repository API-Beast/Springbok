set(H_FILES Easing.h Interpolation.h KeyframeList.h KeyframeList_Templates.hpp)
set(CPP_FILES dummy.cpp)
add_library(sbAnimation OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbAnimation PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbAnimation PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbAnimation PROPERTY OBJ_INSTALL_LOCATION Animation)

ADD_SSTEST_FILE(SpringbokTest KeyframeList_Tests.cpp)