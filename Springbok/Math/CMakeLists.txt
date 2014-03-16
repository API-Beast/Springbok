set(H_FILES Operations.h Range.h Range_Templates.hpp)
set(CPP_FILES dummy.cpp) # Template only
add_library(sbMath OBJECT ${H_FILES} ${CPP_FILES})

set_property(TARGET sbMath PROPERTY OBJ_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set_property(TARGET sbMath PROPERTY OBJ_INSTALL_HEADERS ${H_FILES})
set_property(TARGET sbMath PROPERTY OBJ_INSTALL_LOCATION Math)

ADD_SSTEST_FILE(SpringbokTest Operations_Tests.cpp)