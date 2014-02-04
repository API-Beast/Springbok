set(H_FILES Operations.h Radian.h Range.h Range_Templates.hpp)
set(CPP_FILES dummy.cpp) # Template only
add_library(sbMath STATIC ${H_FILES} ${CPP_FILES})
set_property(TARGET sbMath PROPERTY POSITION_INDEPENDENT_CODE ON)
ADD_SSTEST_FILE(SpringbokTest Operations_Tests.cpp)

set_property(TARGET sbMath PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbMath PUBLIC_HEADER DESTINATION include/Springbok/Math ARCHIVE DESTINATION lib/Springbok)