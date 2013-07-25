set(H_FILES Operations.h Radian.h Range.h)
set(CPP_FILES dummy.cpp) # Template only
add_library(sbMath STATIC ${H_FILES} ${CPP_FILES})
ADD_SSTEST_FILE(SpringbokTest Operations_Tests.cpp)