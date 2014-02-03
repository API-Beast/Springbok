set(H_FILES Easing.h Interpolation.h KeyframeList.h KeyframeList_Templates.hpp)
set(CPP_FILES dummy.cpp) # Template library so far.
add_library(sbAnimation STATIC ${H_FILES} ${CPP_FILES})
ADD_SSTEST_FILE(SpringbokTest KeyframeList_Examples.cpp)

set_property(TARGET sbAnimation PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbAnimation PUBLIC_HEADER DESTINATION include/Springbok/Animation ARCHIVE DESTINATION lib/Springbok)