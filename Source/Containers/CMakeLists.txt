set(H_FILES Associative.h Ringbuffer.h List.h List_Templates.hpp SkipList.h SkipList_Templates.hpp)
set(CPP_FILES dummy.cpp)
add_library(sbContainers STATIC ${H_FILES} ${CPP_FILES})
set_property(TARGET sbContainers PROPERTY POSITION_INDEPENDENT_CODE ON)
ADD_SSTEST_FILE(SpringbokTest List_Examples.cpp)

set_property(TARGET sbContainers PROPERTY PUBLIC_HEADER ${H_FILES})
install(TARGETS sbContainers PUBLIC_HEADER DESTINATION include/Springbok/Containers ARCHIVE DESTINATION lib/Springbok)